#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "util.hpp"

namespace util
{
    bool percent_error(double value, double base, double percent)
    {
        return std::abs((value - base) / base) * 100 < percent;
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
}
