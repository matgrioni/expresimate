#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

#include "new_user.hpp"
#include "user.hpp"

NewUser::NewUser(std::vector<User> users) : users_(users)
{ }

void NewUser::operator() ()
{
    std::ofstream users("./data/users.dat", std::ios::app);

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
    users << u.pickle() << std::endl;

    users.close();
}

bool NewUser::user_name_exists(std::string name)
{
    auto it = std::find_if(users_.begin(),
                           users_.end(),
                           [name] (User u) { return u.name() == name; });
    return it != users_.end();
}
