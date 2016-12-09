#include <iostream>
#include <vector>

#include "expression.hpp"
#include "expression_factory.hpp"
#include "start.hpp"
#include "user.hpp"
#include "util.hpp"

Start::Start()
{ }

void Start::operator() ()
{
    std::vector<User> users;
    util::load_users(users);

    int number_of_players;
    std::cout << std::endl << "Number of players > ";
    std::cin >> number_of_players;

    std::vector<User> cur_users;

    std::cout << "Choose your user..." << std::endl;

    int index = 1;
    for (std::vector<User>::iterator iter = users.begin();
         iter != users.end();
         iter++)
    {
        std::cout << index << ". " << iter->name() << std::endl;

        index++;
    }

    for (int i = 0; i < number_of_players; i++)
    {
        int user_idx;
        do
        {
            std::cout << "Number for user " << i + 1 << " > ";
            std::cin >> user_idx;
        }
        while (user_idx < 1 || user_idx > users.size());

        User u = users[user_idx - 1];
        cur_users.push_back(u);
    }

    ExpressionFactory factory;

    while(true)
    {
        Expression e = factory.create(4, 0, 10);

        double guess;
        std::cout << std::endl << e.expr() << std::endl;
        std::cout << "Guess? > ";
        std::cin >> guess;

        double answer = e.eval();
        if (util::percent_error(guess, answer, 10))
            std::cout << "Close enough!" << std::endl;
        else
            std::cout << "Wayyy off :(" << std::endl;

        std::cout << "The actual answer was " << answer << std::endl;
    }
}
