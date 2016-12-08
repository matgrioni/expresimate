#include <iostream>
#include <cmath>
#include <string>

#include "expression.hpp"
#include "tree.hpp"

Expression::Expression(std::string expr)
{
    tree_ = new BinaryTree<std::string>();

    expr_ = expr;
    parse_(expr_, tree_);
}

Expression::~Expression()
{
    delete tree_;
}

double Expression::eval()
{
    return eval_helper(tree_);
}

std::string Expression::expr()
{
    return expr_;
}

double Expression::eval_helper(BinaryTree<std::string>* tree)
{
    double result;
    std::string root = tree->node();

    if (tree->height() > 0)
    {
        double lhs = eval_helper(tree->left());
        double rhs = eval_helper(tree->right());

        if (root == "+")
            result = lhs + rhs;
        else if (root == "-")
            result = lhs - rhs;
        else if (root == "*")
            result = lhs * rhs;
        else if (root == "/")
            result = lhs / rhs;
        else if (root == "^")
            result = pow(lhs, rhs);
    }
    else
    {
        result = stod(root);
    }

    return result;
}

void Expression::parse_(std::string expr, BinaryTree<std::string>* tree)
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
    {
        if (ops[i] > -1)
        {
            opIndex = ops[i];
            break;
        }
    }

    if (opIndex > -1)
    {
        char op = expr.at(opIndex);
        tree->node(std::string(1, op));

        BinaryTree<std::string> *left = new BinaryTree<std::string>();
        BinaryTree<std::string> *right = new BinaryTree<std::string>();

        std::string lhs = expr.substr(0, opIndex);
        std::string rhs = expr.substr(opIndex + 1);

        parse_(lhs, left);
        parse_(rhs, right);

        tree->left(left);
        tree->right(right);
    }
    else
    {
        tree->node(expr);
    }
}
