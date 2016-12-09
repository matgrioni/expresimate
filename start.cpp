#include <iostream>

#include "start.hpp"

void StartEntryCallback::operator() ()
{
    std::cout << "I am called" << std::endl;
}
