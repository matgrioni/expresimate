#include <algorithm>
#include <iostream>

#include "menu.hpp"

const std::string Menu::QUIT = "Quit";

// TODO: Create functor for add_entry and remove_entry algorithms
bool Menu::add_entry(std::string title, std::function<void()> func)
{
    std::vector<MenuEntry>::iterator it;
    it = std::find_if(entries_.begin(), entries_.end(),
                      [title] (MenuEntry entry) { return entry.title == title; });

    // If there was no entry with the given title.
    bool added;
    if ((added = (it == entries_.end())))
    {
        MenuEntry entry = { title, func };
        entries_.push_back(entry);
    }

    return added;
}

bool Menu::remove_entry(std::string title)
{
    std::vector<MenuEntry>::size_type begin_size = entries_.size();
    std::remove_if(entries_.begin(), entries_.end(),
                   [title] (MenuEntry entry) { return entry.title == title; });

    return begin_size == entries_.size();
}

void Menu::run()
{
    MenuEntry entry = { QUIT, std::bind(&Menu::quit, this) };
    entries_.push_back(entry);

    running = true;
    while (running)
    {
        // TODO: Two counters around one for loop. Find better way
        int index = 1;
        for (std::vector<MenuEntry>::iterator iter = entries_.begin();
             iter != entries_.end();
             iter++)
        {
            std::cout << index << ". " << iter->title << std::endl;
            index++;
        }

        // TODO: Add error message here.
        std::vector<MenuEntry>::size_type option;
        do
        {
            std::cout << "> ";
            std::cin >> option;
        }
        while (option < 1 || option > entries_.size());

        // Now that option is selected, run the associated callback.
        entries_[option - 1].func();
    }
}

void Menu::clear()
{
    entries_.clear();
}

void Menu::quit()
{
    running = false;
}
