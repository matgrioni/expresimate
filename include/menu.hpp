#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <vector>
#include <functional>

typedef struct
{
    std::string title;
    std::function<void()> func;
} MenuEntry;

/*********************************************************************
 * A basic command line menu. Provide the desired options as a
 * menu entry. A menu entry consists of a name or title of the option
 * and a method to invoke on the option being selected. There is a
 * exit option that is automatically added to end the loop. So to use
 * the Menu, simply instantiate it and then run it.
 ********************************************************************/
class Menu
{
    public:
        /* Provide the title for the menu entry, and the callback to
           run when that entry is selected. The prototype of the
           method has no return type and no parameters, since it is
           just encapsulable logic. Further, no duplicate entries are
           allowed, so this function returns false if the title
           already exists and true otherwise. */
        bool add_entry(std::string title, std::function<void()> func);

        /* Removes an entry from the list based on the title given.
           Returns true if the entry was removed, and false
           otherwise. */
        bool remove_entry(std::string title);

        void run();

        /* Clear all the entries in the menu. */
        void clear();

    private:
        /* Sets the private variable running to false. So if the menu
           is currently running, it will be stopped. No effect,
           otherwise. */
        void quit();

        static const std::string QUIT;
        std::vector<MenuEntry> entries_;
        bool running;
};

#endif
