#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "util.hpp"
#include "user.hpp"

namespace util
{
    double percent_error(double value, double base)
    {
        // Prevent divide by 0 if theoretical is 0.
        if (base == 0)
            base = 1;
        return std::abs((value - base) / base) * 100;
    }

    void load_users(std::vector<User> &users)
    {
        std::ifstream users_file("./data/users.dat");

        std::string pickle;
        User u;

        while (getline(users_file, pickle))
        {
            u.depickle(pickle);
            users.push_back(u);
        }

        users_file.close();
    }

    void save_users(std::vector<User> users)
    {
        std::vector<User> saved_users;
        load_users(saved_users);

        std::ofstream users_file("./data/users.dat");

        for (std::vector<User>::iterator it = saved_users.begin();
             it != saved_users.end();
             it++)
        {
            // If the current user is to be updated since it was in
            // the provided list, then copy it over.
            std::string name = it->name();
            auto result = std::find_if(users.begin(), users.end(),
                                      [name] (User u) { return name == u.name(); });
            if (result != users.end())
            {
                users_file << result->pickle();
                users.erase(result);
            }
            else
            {
                users_file << it->pickle();
            }

            users_file << std::endl;
        }

        // For any remaining users that are new and not updating, save
        // them in the file.
        for (std::vector<User>::iterator it = users.begin();
             it != users.end();
             it++)
        {
            users_file << it->pickle();
            users_file << std::endl;
        }

        users_file.close();
    }
}
