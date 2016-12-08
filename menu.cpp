#include <algorithm>
#include <iostream>

#include "menu.hpp"

// TODO: Create functor for add_entry and remove_entry algorithms
bool Menu::add_entry(std::string title, void (*func)(void))
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
    int begin_size = entries_.size();
    std::remove_if(entries_.begin(), entries_.end(),
                   [title] (MenuEntry entry) { return entry.title == title; });

    return begin_size == entries_.size();
}

void Menu::run()
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
    int option;
    do
    {
        std::cout << "> ";
        std::cin >> option;
    }
    while (option < 1 || option > entries_.size());

    // Now that option is selected, run the associated callback.
    entries_[option - 1].func();
}

void Menu::clear()
{
    entries_.clear();
}
