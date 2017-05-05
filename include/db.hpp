#ifndef DB_HPP
#define DB_HPP

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// TODO: Can I separate interface from implementation here.

template <class T>
class DB
{
    public:
        /* Create or open a DB from the provided file. */
        DB(std::string filename);
        void open();

        std::vector<T> all() const;
        int size() const;

        /* Basic operations on the database objects. remove and update return
           true if the operation changed the underlying data and false
           otherwise. */
        void add(T item);
        bool remove(T item);
        bool update(T old_item, T new_item);

        void commit();

    private:
        /* Virtual methods regarding how to recreate and destruct a
           model into its serializable parts. construct creates a
           model given the fields that are extracted from a line in
           the store. destruct creates the vector of fields that is
           written to the store. */
        virtual T construct(const std::vector<std::string> fields) = 0;
        virtual std::vector<std::string> destruct(T item) = 0;

        /* Methods used to handle the conversion between a line and
           vector of fields. parse transforms a line from the db
           store, into a vector of the values stored in the string.
           The model uses the values in vector to reconstruct itself.
           reduce transforms the given vector of fields, which
           represents the different fields into one continuous string
           to save in the store. */
        std::vector<std::string> parse(std::string line);
        std::string reduce(std::vector<std::string> fields);

        std::string filename_;
        std::vector<T> items_;
};

template <class T>
DB<T>::DB(std::string filename)
{
    filename_ = filename;
}

template <class T>
void DB<T>::open()
{
    std::ifstream store(filename_);

    // Create an item T for each line in the database and then add it
    // to the items vector.
    std::string line;
    while (getline(store, line))
    {
        std::vector<std::string> fields = parse(line);
        items_.push_back(construct(fields));
    }

    store.close();
}

template <class T>
std::vector<T> DB<T>::all() const
{
    return items_;
}

template <class T>
int DB<T>::size() const
{
    return items_.size();
}

template <class T>
void DB<T>::add(T item)
{
    items_.push_back(item);
}

template <class T>
bool DB<T>::remove(T item)
{
    typename std::vector<T>::iterator it = std::find(items_.begin(),
                                                     items_.end(), item);
    if (it != items_.end())
    {
        items_.erase(it);
        return true;
    }

    return false;
}

template <class T>
bool DB<T>::update(T old_item, T new_item)
{
    typename std::vector<T>::iterator it = std::find(items_.begin(),
                                                     items_.end(), old_item);
    if (it != items_.end())
    {
        *it = new_item;
        return true;
    }

    return false;
}

template <class T>
void DB<T>::commit()
{
    std::ofstream store(filename_, std::ios::trunc);

    for (T item : items_)
    {
        std::vector<std::string> fields = destruct(item);
        store << reduce(fields) << std::endl;
    }

    store.close();
}

template <class T>
std::vector<std::string> DB<T>::parse(std::string line)
{
    std::vector<std::string> fields;
    std::stringstream ss;

    for (int i = 0; i < line.length(); i++)
    {
        char cur = line.at(i);

        if (cur == '\t')
        {
            fields.push_back(ss.str());
            ss.str("");
        }
        else
        {
            ss << cur;
        }
    }

    fields.push_back(ss.str());

    return fields;
}

template <class T>
std::string DB<T>::reduce(std::vector<std::string> fields)
{
    std::stringstream ss;

    // When iterating do not add a tab at the end to the reduced
    // string. So iterate through all fields except the last and add
    // that one manually.
    for (std::vector<std::string>::iterator iter = fields.begin();
         iter != fields.end() - 1;
         iter++)
    {
        ss << *iter << "\t";
    }

    ss << fields.back();

    return ss.str();
}

#endif
