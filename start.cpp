#include <chrono>
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
    std::vector<GameSession> sessions;

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
        sessions.push_back(GameSession());
    }

    ExpressionFactory factory;

    int turn = 0;
    bool one_alive = true;
    while(one_alive)
    {
        User &cur_user = chosen_users[turn];
        GameSession &cur_session = sessions[turn];

        std::cout << std::endl << cur_user.name() << "'s turn!" << std::endl;
        std::cout << "Round " << cur_session.round << std::endl;
        std::cout << "Hit any <enter> when ready!" << std::endl;
        std::cin.ignore(255, '\n');
        std::cin.get();

        // Every other round the number of terms goes up one and every
        // other round the max goes up by 2.
        int terms = 2 + (cur_session.round - 1) / 2;
        int max = 10 + cur_session.round - (cur_session.round % 2);
        Expression e = factory.create(terms, 0, max);

        // Used to keep track of how much time it took the user to
        // input a guess. If it is more than 10 seconds, then they
        // get no points.
        auto start = std::chrono::system_clock::now();

        double guess;
        std::cout << e.expr() << std::endl;
        std::cout << "Guess? > ";
        std::cin >> guess;

        auto end = std::chrono::system_clock::now();

        double answer = e.eval();
        double error;
        if ((error = util::percent_error(guess, answer)) < 10)
        {
            float dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.f;
            std::cout << "Good!" << std::endl;
            std::cout << "Took " << dur << " s" << std::endl;

            cur_session.round++;

            // The harder the problem is, the closer they are, and the
            // less time they take, the more points they get.
            int gained = (max + terms) * (10 - error) * ((10 - dur) / 10);
            cur_session.score += gained;
            std::cout << "New score: " << cur_session.score << std::endl;
        }
        else
        {
            std::cout << "Wayyy off :(" << std::endl;
            cur_session.lives--;

            if (cur_session.lives <= 0)
                cur_session.alive = false;
        }
        std::cout << "The actual answer was " << answer << std::endl;
        std::cout << cur_session.lives << " lives left" << std::endl;

        int players_checked = 0;
        do
        {
            turn = (turn + 1) % number_of_players;
            players_checked++;
        }
        while (!sessions[turn].alive && players_checked < number_of_players);

        one_alive = sessions[turn].alive;
    }

    std::cout << "Everybody's lost their chance!" << std::endl;
    // TODO: Reusing variable, find better way to iterate over vector
    index = 0;
    for (GameSession g : sessions)
    {
        chosen_users[index].highscore(g.score);
        index++;
    }

    util::save_users(chosen_users);
}
