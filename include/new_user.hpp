#ifndef NEW_PLAYER_CALLBACK_HPP
#define NEW_PLAYER_CALLBACK_HPP

#include <string>
#include <vector>

#include "user.hpp"

class NewUser
{
    public:
        NewUser();
        void operator() ();

    private:
        bool user_name_exists(std::string name);

        std::vector<User> users_;
};

#endif
