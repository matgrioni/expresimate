#include <cstdlib>
#include <fstream>
#include <iostream>

#include "start.hpp"
#include "new_user.hpp"
#include "highscores.hpp"
#include "menu.hpp"

void quit();

int main()
{
    Menu m;
    m.add_entry("Start", Start());
    m.add_entry("New user", NewUser());
    m.add_entry("Highscores", Highscores());
    m.add_entry("Quit", quit);

    m.run();

    return 0;
}

void quit()
{
    exit(0);
}
