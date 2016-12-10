#ifndef START_HPP
#define START_HPP

#include <vector>

#include "user.hpp"

typedef struct GameSession
{
    GameSession() : lives(3), round(1), alive(true) { }

    int lives;
    int round;
    bool alive;
} GameSession;

class Start
{
    public:
        Start();
        void operator() ();
};

#endif
