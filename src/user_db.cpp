#include "user.hpp"
#include "user_db.hpp"

#include <string>
#include <vector>

User UserDB::construct(const std::vector<std::string> fields)
{
    long id = std::stol(fields[0]);
    std::string name = fields[1];
    int age = std::stoi(fields[2]);
    int highscore = std::stoi(fields[3]);

    return User(id, name, age, highscore);
}

std::vector<std::string> UserDB::destruct(User u)
{
    std::vector<std::string> fields;

    fields.push_back(std::to_string(u.id()));
    fields.push_back(u.name());
    fields.push_back(std::to_string(u.age()));
    fields.push_back(std::to_string(u.highscore()));

    return fields;
}
