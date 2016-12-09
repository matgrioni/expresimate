#ifndef UTIL_HPP
#define UTIL_HPP

#include <vector>

#include "user.hpp"

namespace util
{
    bool percent_error(double value, double base, double percent);

    /* Loads users stored in data/users.dat into vector reference
     * provided. */
    void load_users(std::vector<User> &users);
}

#endif
