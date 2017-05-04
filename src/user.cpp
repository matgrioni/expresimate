#include <sstream>
#include <string>

#include "user.hpp"

User::User() : name_(""), age_(-1), highscore_(0)
{ }

User::User(std::string name) : name_(name), age_(-1), highscore_(-1)
{ }

User::User(std::string name, int age) : name_(name), age_(age), highscore_(-1)
{ }

User::User(std::string name, int age, int highscore) :
    name_(name), age_(age), highscore_(highscore)
{ }

std::string User::name()
{
    return name_;
}

void User::name(std::string new_name)
{
    name_ = new_name;
}

int User::age()
{
    return age_;
}

void User::age(int new_age)
{
    age_ = new_age;
}

int User::highscore()
{
    return highscore_;
}

bool User::highscore(int new_score)
{
    if (new_score > highscore_)
    {
        highscore_ = new_score;
        return true;
    }

    return false;
}

bool User::operator==(const User& u)
{
    return name_ == u.name_;
}
