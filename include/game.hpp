#ifndef GAME_HPP
#define GAME_HPP

typedef struct GameSession
{
    GameSession() : lives(3), round(1), alive(true), score(0) { }

    int lives;
    int round;
    bool alive;
    int score;
} GameSession;

class Game
{
    public:
        void operator() ();

    private:
        static const int MAX_START = 10;
        static const int TERMS_EXPR_START = 2;

        static constexpr double PERCENT_ERROR = 10;
        static constexpr double TIME_ALLOWED = 10;
};

#endif
