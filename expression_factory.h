#ifndef EXPRESSION_FACTORY_H
#define EXPRESSION_FACTORY_H

#include "expression.h"

class ExpressionFactory
{
    public:
        Expression create(int terms, double min, double max);
};

#endif
