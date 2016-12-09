#include <fstream>
#include <iostream>
#include <vector>

#include "expression_factory.hpp"
#include "start.hpp"
#include "new_user.hpp"
#include "menu.hpp"
#include "user.hpp"

/* Loads users stored in data/users.dat into vector reference
 * provided. */
void load_users(std::vector<User> &users);

int main()
{
    std::vector<User> users;
    load_users(users);

    ExpressionFactory factory;
    Expression e = factory.create(2, 0, 10);

    Menu m;
    m.add_entry("Start", Start(users));
    m.add_entry("New user", NewUser(users));

    m.run();

    return 0;
}

void load_users(std::vector<User> &users)
{
    std::ifstream users_file("./data/users.dat");

    std::string pickle;
    User u;

    while (getline(users_file, pickle))
    {
        u.depickle(pickle);
        users.push_back(u);
    }

    users_file.close();
}
