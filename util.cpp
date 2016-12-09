#include <cmath>

#include "util.hpp"

namespace util
{
    bool percent_error(double value, double base, double percent)
    {
        return std::abs((value - base)) / base < percent;
    }
}
