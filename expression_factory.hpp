#ifndef EXPRESSION_FACTORY_HPP
#define EXPRESSION_FACTORY_HPP

#include "expression.hpp"

class ExpressionFactory
{
    public:
        Expression create(int terms, int min, int max);
};

#endif
