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

    int term;
    char op;
    char prev_op = '\0';
    std::stringstream ss;
    for (int i = 0; i < terms; i++)
    {
        // Make sure no divide by zero.
        do
        {
            term = term_dis(gen);
            op = ops[op_dis(gen)];
        }
        while (prev_op == '/' && term == 0);

        ss << term;
        if (i < terms - 1)
            ss << op;

        prev_op = op;
    }

    return Expression(ss.str());
}
