#ifndef UTIL_HPP
#define UTIL_HPP

#include <vector>

#include "user.hpp"

namespace util
{
    double percent_error(double value, double base);

    /* Loads users stored in data/users.dat into vector reference
     * provided. */
    void load_users(std::vector<User> &users);
}

#endif
