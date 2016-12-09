#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "new_user.hpp"
#include "user.hpp"
#include "util.hpp"

NewUser::NewUser()
{ }

void NewUser::operator() ()
{
    util::load_users(users_);

    std::ofstream users_file("./data/users.dat", std::ios::app);

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
    users_file << u.pickle() << std::endl;

    users_file.close();
}

bool NewUser::user_name_exists(std::string name)
{
    auto it = std::find_if(users_.begin(),
                           users_.end(),
                           [name] (User u) { return u.name() == name; });
    return it != users_.end();
}
