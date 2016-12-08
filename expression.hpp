#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include "tree.hpp"

/*********************************************************************
*
* An arithmetic expression that can be evaluated. The expression can
* have no parenthesis, and can have the operators +, -, *, /, and ^.
*
*********************************************************************/
class Expression
{
    public:
        Expression(std::string expr);
        ~Expression();

        double eval();

        std::string expr();

    private:
        double eval_helper(BinaryTree<std::string>* tree);
        void parse_(std::string expr, BinaryTree<std::string>* tree);

        BinaryTree<std::string> *tree_;
        std::string expr_;
};

#endif
