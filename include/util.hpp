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

    /* This saves the given users into the data/users.dat store. If
     * the user already exists, the record is updated. Otherwise,
     * a new entry is made. */
    void save_users(std::vector<User> users);

    /* Removes the given users from the data/users.dat store if they
     * exist. Returns false it the user does not exist, and true
     * otherwise. */
    bool remove_user(User user);
}

#endif
