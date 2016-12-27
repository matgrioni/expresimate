#include <algorithm>
#include <fstream>
#include <string>

#include "db.hpp"

DB::DB(std::string filename)
{
    filename_ = filename;
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

DB::~DB()
{
    // TODO: Are both flags needed?
    std::ofstream store(filename_, std::ios::out | std::ios::trunc);

    for (T item : items_)
    {
        std::vector<std::string> fields = destruct(item);
        store << reduce(fields) << std::endl;
    }

    store.close();
}

std::vector<T> DB::all() const
{
    return items_;
}

void DB::add(T item)
{
    items_.push_back(item);
}

bool DB::remove(T item)
{
    items_.erase(std::remove(items_.begin(), items_.end(), item), items_.end());
}

std::vector<std::string> DB::parse(std::string line)
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


}

std::string DB::reduce(std::vector<std::string> fields)
{
    std::stringstream ss;

    // When iterating do not add a tab at the end to the reduced
    // string. So iterate through all fields except the last and add
    // that one manually.
    for (std::vector<std::string>::iterator iter = fields.begin();
         iter != fields.end() - 1;
         iter++)
    {
        ss << s << "\t";
    }

    ss << fields.back();

    return ss.str();
}
