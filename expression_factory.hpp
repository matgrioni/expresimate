#ifndef EXPRESSION_FACTORY_HPP
#define EXPRESSION_FACTORY_HPP

#include "expression.hpp"

class ExpressionFactory
{
    public:
        Expression create(int terms, double min, double max);
};

#endif
