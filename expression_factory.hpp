#ifndef EXPRESSION_FACTORY_HPP
#define EXPRESSION_FACTORY_HPP

#include "expression.hpp"

class ExpressionFactory
{
    public:
        /* Creates an Expression given the number of terms to be in
         * the expression and range of values that the terms can take
         * as integers. */
        Expression create(int terms, int min, int max);
};

#endif
