#include <sstream>
#include <string>

#include "user.hpp"

User::User() : name_(""), age_(-1), score_(0)
{ }

User::User(std::string name)
{
    name_ = name;
    age_ = -1;
    score_ = 0;
}

User::User(std::string name, int age)
{
    name_ = name;
    age_ = age;
    score_ = 0;
}

int User::age()
{
    return age_;
}

void User::age(int new_age)
{
    age_ = new_age;
}

int User::score()
{
    return score_;
}

void User::score(int new_score)
{
    score_ = new_score;
}

std::string User::pickle()
{
    std::stringstream ss;
    ss << "{ name: " << name_ << " }";
    ss << ", { age: " << age_ << " }";
    ss << ", { score: " << score_ << " }";

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
    score_ = std::stoi(values[2]);
}
