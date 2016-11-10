#include <string>

#include "expression.h"
#include "tree.h"

Expression::Expression(std::string expr)
{
    expr_ = expr;
    parse_(expr_, tree_);
}

void Expression::parse_(std::string expr, BinaryTree<std::string> &tree)
{
    // The first indexes for each class of operator in the expression.
    // ops[0] is for '+' and '-' operators.
    // ops[1] is for '*' and '/' operators.
    // ops[2] is for the '^' operator.
    int ops[] = { -1, -1, -1 };
    int index = 0;
    while(ops[0] < 0 && index < expr.length())
    {
        char cur = expr.at(index);
        if (cur == '+' || cur == '-')
            ops[0] = index;
        else if (cur == '*' || cur == '/')
            ops[1] = index;
        else if (cur == '^')
            ops[2] = index;

        index++;
    }

    int opIndex = -1;
    for (int i = 0; i < 3; i++)
        if (ops[i] > -1)
            opIndex = ops[i];
}
