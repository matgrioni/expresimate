#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>

#include "expression.hpp"
#include "expression_factory.hpp"
#include "game.hpp"
#include "user.hpp"
#include "user_db.hpp"
#include "util.hpp"

void Game::operator() ()
{
    UserDB userDB(util::USER_STORE);
    userDB.open();

    std::vector<User> users = userDB.all();

    int number_of_players;
    std::cout << std::endl << "Number of players (>1) > ";
    do
    {
        std::cin >> number_of_players;
    } while (number_of_players <= 0 || number_of_players > users.size());

    std::vector<User> chosen_users;
    std::vector<GameSession> sessions;

    std::cout << "Choose your user..." << std::endl;

    for (std::vector<User>::size_type i = 1; i <= users.size(); i++)
        std::cout << i << ". " << users[i - 1].name() << std::endl;

    for (int i = 1; i <= number_of_players; i++)
    {
        std::vector<User>::size_type user_idx;
        do
        {
            std::cout << "Number for user " << i << " > ";
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
        std::cout << "Hit <enter> when ready!" << std::endl;
        std::cin.ignore(255, '\n');
        std::cin.get();

        // Every other round the number of terms goes up one and every
        // other round the max goes up by 2.
        int terms = TERMS_EXPR_START + (cur_session.round - 1) / 2;
        int max = TERMS_EXPR_START + cur_session.round - (cur_session.round % 2);
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
        double dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.f;
        std::cout << "Took " << dur << " s" << std::endl;

        double answer = e.eval();
        double error;
        if (answer == 0)
            // Allow the guesser to be within the range (-0.2, 0.2)
            // when the expected answer is 0.
            error = std::abs(guess / 2) * 100;
        else
            error = util::percent_error(guess, answer);

        // The harder the problem is, the closer they are, and the less time
        // they take, the more points they get. Keep the point losing at most to
        // -100.
        int diff = std::abs(((max + terms) * (PERCENT_ERROR - error) *
                            (TIME_ALLOWED - dur) / TIME_ALLOWED));
        if (diff < -100)
            diff = -100;

        if (error < PERCENT_ERROR && dur < TIME_ALLOWED)
        {
            std::cout << "Good!" << std::endl;

            cur_session.round++;
            cur_session.score += diff;
            std::cout << "New score: " << cur_session.score << std::endl;
        }
        else
        {
            std::cout << "Sorry :(" << std::endl;
            cur_session.score -= diff;
            cur_session.lives--;

            if (cur_session.lives <= 0)
            {
                cur_session.alive = false;
                std::cout << "Final score: " << cur_session.score << std::endl;
            }
            else
                std::cout << "New score: " << cur_session.score << std::endl;
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

        // Once we break out of the loop, this means that we either checked
        // through every game session and did not find another one left alive in
        // which case the current user is not alive. Otherwise, we found a user
        // whose turn it is and they are currently alive.
        one_alive = sessions[turn].alive;
    }

    std::cout << "Everybody's lost their chance!" << std::endl << std::endl;
    for (std::vector<GameSession>::size_type i = 0; i < sessions.size(); i++)
    {
        User n_u = chosen_users[i];

        bool best = n_u.highscore(sessions[i].score);
        if (best)
        {
            userDB.update(chosen_users[i], n_u);
            std::cout << chosen_users[i].name() << " has a new highscore"
                      << std::endl;
        }
    }

    userDB.commit();
}
