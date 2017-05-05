#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>

namespace util
{
    static const std::string USER_STORE = "./data/users.dat";

    double percent_error(double value, double base);
}

#endif
