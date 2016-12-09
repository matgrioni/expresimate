#include <iostream>

#include "start.hpp"

Start::Start()
{

}

void Start::operator() ()
{
    std::cout << "I am called" << std::endl;
}
