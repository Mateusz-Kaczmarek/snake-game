#pragma once
#include "Snake.hpp"
#include "Food.hpp"
#include "Board.hpp"
#include "MoveDirection.hpp"

class Game
{
public:
    Game(int, int);
    void startGame();

private:
    void sleepGame(int milliseconds);
    void clearScreen();
    void reactionOnKeyboard(const char);
    bool isNewDirectionValid(const char);
    bool isCollision();
    int kbhit();

    Board mBoard;
    Snake mSnake;
    Food  mFood;
    unsigned int mSleepTime = 200;
    int mNextLvl = 3;
    int mScore = 0;
    int mFrames = 0;
    MoveDirection mDirection = MoveDirection::RIGHT;
};
