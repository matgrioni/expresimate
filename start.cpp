#include <iostream>

#include "expression.hpp"
#include "expression_factory.hpp"
#include "start.hpp"
#include "util.hpp"

Start::Start(std::vector<User> users) : users_(users)
{ }

void Start::operator() ()
{
    std::cout << std::endl << "Choose your user..." << std::endl;

    int index = 1;
    for (std::vector<User>::iterator iter = users_.begin();
         iter != users_.end();
         iter++)
    {
        std::cout << index << ". " << iter->name() << std::endl;

        index++;
    }

    int user_idx;
    do
    {
        std::cout << "User number > ";
        std::cin >> user_idx;
    }
    while (user_idx < 1 || user_idx > users_.size());
    User u = users_[user_idx - 1];

    ExpressionFactory factory;

    while(true)
    {
        Expression e = factory.create(4, 0, 10);

        double guess;
        std::cout << std::endl << e.expr() << std::endl;
        std::cout << "Guess? > ";
        std::cin >> guess;

        double answer = e.eval();
        if (util::percent_error(guess, e.eval(), 10))
            std::cout << "Close enough!" << std::endl;
        else
            std::cout << "Wayyy off :(" << std::endl;

        std::cout << "The actual answer was " << answer << std::endl;
    }
}
