#include <cmath>
#include <fstream>
#include <iostream>
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
}
