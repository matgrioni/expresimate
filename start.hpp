#ifndef START_HPP
#define START_HPP

#include <vector>

#include "user.hpp"

typedef struct GameSession
{
    GameSession() : lives(3), round(1), alive(true), score(0) { }

    int lives;
    int round;
    bool alive;
    int score;
} GameSession;

class Start
{
    public:
        Start();
        void operator() ();
};

#endif
