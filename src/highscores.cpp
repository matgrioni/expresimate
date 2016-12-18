#include <algorithm>
#include <iostream>
#include <vector>

#include "highscores.hpp"
#include "user.hpp"
#include "util.hpp"

void Highscores::operator() ()
{
    std::vector<User> users;
    util::load_users(users);

    std::sort(users.begin(), users.end(),
              [] (User a, User b) { return a.highscore() < b.highscore(); });

    std::cout << std::endl << "Highscores" << std::endl;
    for (User u : users)
    {
        std::cout << u.name() << ": " << u.highscore() << std::endl;
    }

    std::cout << std::endl;
}
