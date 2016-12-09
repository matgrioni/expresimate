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

    std::vector<User> chosen_users;

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
        chosen_users.push_back(u);
    }

    ExpressionFactory factory;

    int terms = 2;
    int max = 10;
    int round = 1;
    int turn = 0;
    while(true)
    {
        User &cur_user = chosen_users[turn];
        std::cout << std::endl << cur_user.name() << "'s turn!" << std::endl;
        std::cout << "Round " << round << std::endl;

        Expression e = factory.create(terms, 0, max);

        double guess;
        std::cout << e.expr() << std::endl;
        std::cout << "Guess? > ";
        std::cin >> guess;

        double answer = e.eval();
        double error;
        if ((error = util::percent_error(guess, answer)) < 10)
        {
            std::cout << "Good for me!" << std::endl;

            round++;
            if (round % 2 == 0)
                max += 2;
            else
                terms++;

            int gained = (max + terms) * (10 - error);
            cur_user.score(cur_user.score() + gained);
            std::cout << "New score: " << cur_user.score() << std::endl;

            turn = (turn + 1) % number_of_players;
        }
        else
            std::cout << "Wayyy off :(" << std::endl;

        std::cout << "The actual answer was " << answer << std::endl;
    }
}
