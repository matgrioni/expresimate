#include <fstream>
#include <iostream>
#include <string>

#include "new_user.hpp"
#include "user.hpp"

void NewUser::operator() ()
{
    std::ofstream users("./data/users.dat", std::ios::app);

    std::string name;
    std::cout << "Player name > ";
    std::cin.ignore(100, '\n');
    getline(std::cin, name);

    int age;
    std::cout << "Age > ";
    std::cin >> age;

    User u(name, age);
    users << u.pickle() << std::endl;

    users.close();
}
