#include <algorithm>
#include <iostream>
#include <vector>

#include "highscores.hpp"
#include "user.hpp"
#include "user_db.hpp"
#include "util.hpp"

void Highscores::operator() ()
{
    UserDB userDB(util::USER_STORE);
    userDB.open();

    std::vector<User> users = userDB.all();

    if (users.size() > 0)
    {
        std::sort(users.begin(), users.end(),
                  [] (User a, User b) { return a.highscore() > b.highscore(); });

        std::cout << std::endl << "Highscores" << std::endl;
        for (User u : users)
        {
            std::cout << u.name() << ": " << u.highscore() << std::endl;
        }

        std::cout << std::endl;
    }
    else
        std::cout << "There are no users." << std::endl;
}
