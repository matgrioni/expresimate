#include <cmath>

#include "util.hpp"

namespace util
{
    double percent_error(double value, double base)
    {
        return std::abs((value - base) / base) * 100;
    }
}
