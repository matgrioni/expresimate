#ifndef DB_HPP
#define DB_HPP

#include <string>
#include <vector>

template <class T>
class DB
{
    public:
        /* Create a DB from the provided file. */
        DB(std::string filename);
        virtual ~DB();

        std::vector<T> all() const;

        void add(T item);

        /* Removes the given item if it exists from the database. If
           the item does not exist returns false, true otherwise. */
        bool remove(T item);

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

#endif
