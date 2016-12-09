#include <iostream>
#include <random>
#include <sstream>

#include "expression_factory.hpp"
#include "expression.hpp"

Expression ExpressionFactory::create(int terms, int min, int max)
{
    char ops[] = { '+', '-', '*', '/' };

    // Initialize random number distribution.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> term_dis(min, max),
                                    op_dis(0, 3);

    std::stringstream ss;
    for (int i = 0; i < terms - 1; i++)
        ss << term_dis(gen) << ops[op_dis(gen)];
    ss << term_dis(gen);

    return Expression(ss.str());
}
