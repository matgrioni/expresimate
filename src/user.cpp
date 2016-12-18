#include <sstream>
#include <string>

#include "user.hpp"

User::User() : name_(""), age_(-1), highscore_(0)
{ }

User::User(std::string name)
{
    name_ = name;
    age_ = -1;
    highscore_ = 0;
}

User::User(std::string name, int age)
{
    name_ = name;
    age_ = age;
    highscore_ = 0;
}

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

std::string User::pickle()
{
    std::stringstream ss;
    ss << "{ name: " << name_ << " }";
    ss << ", { age: " << age_ << " }";
    ss << ", { highscore: " << highscore_ << " }";

    return ss.str();
}

void User::depickle(std::string pickle)
{
    std::vector<std::string> values;

    int braces = 0;
    bool past_field_name = false;

    int data_start = 0;
    int data_end = 0;
    for (int i = 0; i < pickle.length(); i++)
    {
        char cur = pickle.at(i);
        if (cur == '{')
        {
            braces++;
        }
        else if (cur == '}')
        {
            braces--;
            if (braces == 0)
            {
                if (past_field_name)
                {
                    data_end = i - 1;
                    values.push_back(pickle.substr(data_start, data_end - data_start));
                }
                past_field_name = false;
            }
        }
        else if (cur == ':' && braces > 0 && !past_field_name)
        {
            past_field_name = true;
            data_start = i + 2;
        }
    }

    process_pickle(values);
}

void User::process_pickle(std::vector<std::string> values)
{
    name_ = values[0];
    age_ = std::stoi(values[1]);
    highscore_ = std::stoi(values[2]);
}
