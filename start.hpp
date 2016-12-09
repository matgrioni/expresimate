#ifndef START_HPP
#define START_HPP

#include <vector>

#include "user.hpp"

class Start
{
    public:
        Start(std::vector<User> users);
        void operator() ();

    private:
        std::vector<User> users_;
};

#endif
