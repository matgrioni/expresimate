#include <iostream>
#include <string>

#include "new_user.hpp"
#include "user.hpp"
#include "user_db.hpp"
#include "util.hpp"

NewUser::NewUser()
{ }

void NewUser::operator() ()
{
    UserDB userDB(util::USER_STORE);
    userDB.open();

    std::cin.ignore(100, '\n');
    std::string name;
    std::cout << "Player name > ";
    getline(std::cin, name);

    int age;
    std::cout << "Age > ";
    std::cin >> age;

    User u(User::genID(), name, age);
    userDB.add(u);
    userDB.commit();
}
