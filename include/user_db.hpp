#ifndef USER_DB_HPP
#define USER_DB_HPP

#include "db.hpp"

#include <string>
#include <vector>

class UserDB : public DB<User>
{
    public:
        using DB<User>::DB;

        User construct(const std::vector<std::string> fields);
        std::vector<std::string> destruct(User u);
};

#endif
