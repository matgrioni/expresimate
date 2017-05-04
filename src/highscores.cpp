#include <algorithm>
#include <iostream>
#include <vector>

#include "highscores.hpp"
#include "user.hpp"
#include "user_db.hpp"

void Highscores::operator() ()
{
    UserDB userDB("./data/users.dat");
    userDB.init();

    std::vector<User> users = userDB.all();

    std::sort(users.begin(), users.end(),
              [] (User a, User b) { return a.highscore() < b.highscore(); });

    std::cout << std::endl << "Highscores" << std::endl;
    for (User u : users)
    {
        std::cout << u.name() << ": " << u.highscore() << std::endl;
    }

    std::cout << std::endl;
}
