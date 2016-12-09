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

        std::string name();
        void name(std::string new_name);

        int age();
        void age(int new_age);

        int score();
        void score(int new_score);

        /* Pickling is essentially converting a complex data structure
         * into a simpler one such as a string, and reconstructing
         * an object based on this string. Right now, pickling does
         * not support '{' or '}' in the data. */
        std::string pickle();
        void depickle(std::string pickle);

    private:
        void process_pickle(std::vector<std::string> values);

        std::string name_;
        int age_;
        int score_;
};

#endif
