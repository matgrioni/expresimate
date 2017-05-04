#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <vector>

/*********************************************************************
* A general user or player class that has a given name and score for
* the game. A user instance can be converted to a string and also read
* in from a string which is the output of the as_str function.
*********************************************************************/
class User
{
    public:
        User();
        User(std::string name);
        User(std::string name, int age);
        User(std::string name, int age, int highscore);

        std::string name();
        void name(std::string new_name);

        int age();
        void age(int new_age);

        /* Getters and setters for the highscore. Only difference is
         * that the highscore is only changed if new_score is greater
         * than the current highscore. True is returned if the
         * highscore is changed, and false otherwise. */
        int highscore();
        bool highscore(int new_score);

        bool operator==(const User& u);

    private:
        std::string name_;
        int age_;
        int highscore_;
};

#endif
