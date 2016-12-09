#include <fstream>
#include <iostream>

#include "start.hpp"
#include "new_user.hpp"
#include "menu.hpp"

int main()
{
    Menu m;
    m.add_entry("Start", Start());
    m.add_entry("New user", NewUser());

    m.run();

    return 0;
}

