#pragma once
#include "Snake.hpp"
#include "Food.hpp"
#include "Board.hpp"
#include "MoveDirection.hpp"

class Game
{
public:
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
    int mSleepTime = 200;
    int mNextLvl = 3;
    int mScore = 0;
    int mFrames = 0;
    MoveDirection mDirection = MoveDirection::RIGHT;
};
