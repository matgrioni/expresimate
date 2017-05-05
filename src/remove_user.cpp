#include <iostream>
#include <vector>

#include "remove_user.hpp"
#include "user.hpp"
#include "user_db.hpp"
#include "util.hpp"

void RemoveUser::operator() ()
{
    UserDB userDB(util::USER_STORE);
    userDB.open();

    std::vector<User> users = userDB.all();

    if (users.size() > 0)
    {
        std::cout << std::endl << "Choose user to delete..." << std::endl;
        for (std::vector<User>::size_type i = 1; i <= users.size(); i++)
            std::cout << i << ". " << users[i - 1].name() << std::endl;

        std::vector<User>::size_type u_idx;
        do
        {
            std::cout << "> ";
            std::cin >> u_idx;
        } while (u_idx < 1 || u_idx > users.size());

        userDB.remove(users[u_idx - 1]);
        userDB.commit();
    }
    else
    {
        std::cout << "There are no users to remove." << std::endl;
    }
}
