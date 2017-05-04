#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "new_user.hpp"
#include "user.hpp"
#include "user_db.hpp"

NewUser::NewUser()
{ }

void NewUser::operator() ()
{
    // TODO: Use constants
    UserDB userDB("./data/users.dat");
    userDB.init();

    std::cin.ignore(100, '\n');
    std::string name;
    do
    {
        std::cout << "Player name > ";
        getline(std::cin, name);
    }
    while (user_name_exists(name));

    int age;
    std::cout << "Age > ";
    std::cin >> age;

    User u(name, age);
    userDB.add(u);
    userDB.commit();
}

bool NewUser::user_name_exists(std::string name)
{
    auto it = std::find_if(users_.begin(),
                           users_.end(),
                           [name] (User u) { return u.name() == name; });
    return it != users_.end();
}
