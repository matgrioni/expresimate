#include <iostream>
#include <vector>

#include "remove_user.hpp"
#include "user.hpp"
#include "user_db.hpp"
#include "util.hpp"

void RemoveUser::operator() ()
{
    UserDB userDB("./data/users.dat");
    userDB.open();

    std::vector<User> users = userDB.all();

    std::cout << std::endl << "Choose user to delete..." << std::endl;
    int index = 1;
    for (User u : users)
    {
        std::cout << index << ". " << u.name() << std::endl;

        index++;
    }

    int u_idx;
    do
    {
        std::cout << "> ";
        std::cin >> u_idx;
    } while (u_idx < 1 || u_idx > users.size());

    userDB.remove(users[u_idx - 1]);
    userDB.commit();
}
