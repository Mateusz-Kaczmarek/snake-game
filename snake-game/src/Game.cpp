#include "../inc/Game.hpp"
#include <iostream>
//#include <unistd.h>
#include <chrono>
#include <sys/ioctl.h>
#include <termios.h>

using namespace std::chrono;

namespace
{
    bool valid = true;
    int bytesWaiting;
    Position snakeHead;
}

void Game::startGame()
{
    mBoard.setUpWallInBoard();
    mSnake.setUpSnakeStartPosition();
    mBoard.addSnakeInBoard(mSnake.getSnakePos());
    mBoard.addFoodOnBoard(mFood.getFoodPos());
    clearScreen();

    while (true)
    {
        if(mScore != 0 and mScore == mNextLvl and mSleepTime > 20)
        {
            mNextLvl += 3;
            mSleepTime -= 10;
        }
        mBoard.printBoard(mFrames, mScore);
        sleepGame(mSleepTime);

        if(kbhit())   /// If keyboard hit
        {
            char k;
            std::cin >> k; /// Character
            if(isNewDirectionValid(k))
            {
                reactionOnKeyboard(k);
            }
        }

        mSnake.updateSnakePosition();

        if(mFood.isFoodToEat(mSnake.getSnakePos()))
        {
            mBoard.addFoodOnBoard(mFood.getFoodPos());
            mSnake.addNewSegmentToSnakeBody();
            mScore++;
        }
        else
        {
            mBoard.removeSnakeTaileFromBoard(mSnake.getSnakeTail());
        }

        mBoard.addSnakeInBoard(mSnake.getSnakePos());

        if(isCollision())
        {
            break;
        }

        clearScreen();
        mFrames++;
    }

    std::cout<<"                    GAME OVER"<<std::endl;
    std::cout<<"                   YOUR SCORE: "<<mScore<<std::endl;
}


void Game::sleepGame(int milliseconds)
{
    auto now = system_clock::now();
    system_clock::time_point timeEnd = now + duration<int, std::milli>(milliseconds);
    while (system_clock::now() < timeEnd)
    {
    }
}
void Game::clearScreen()
{
    system("clear");
}

void Game::reactionOnKeyboard(const char ch)
{
    switch (ch)
    {
        case 'j':
            mDirection = MoveDirection::LEFT;
            break;

        case 'l':
            mDirection = MoveDirection::RIGHT;
            break;

        case 'i':
            mDirection = MoveDirection::UP;
            break;

        case 'k':
            mDirection = MoveDirection::DOWN;
            break;

        default:
            break;
    }
}

bool Game::isNewDirectionValid(const char ch)
{
    switch (ch)
    {
        case 'j':
            if(mDirection == MoveDirection::RIGHT)
                valid = false;
            break;

        case 'l':
            if(mDirection == MoveDirection::LEFT)
                valid = false;
            break;

        case 'i':
            if(mDirection == MoveDirection::DOWN)
                valid = false;
            break;

        case 'k':
            if(mDirection == MoveDirection::UP)
                valid = false;
            break;

        default:
            break;
    }

    return valid;
}

bool Game::isCollision()
{
    snakeHead = mSnake.getSnakePos().back();

    if(snakeHead.y == 0 or snakeHead.y == (mBoard.getHeight()-1) or snakeHead.x == 0 or snakeHead.x == (mBoard.getWidth()-1))
    {
        return true;
    }

    //check in snake body if head exist more than once
     if(mSnake.isColisionWithOwnBoady())
     {
        return true;
     }

    return false;
}

int Game::kbhit()
{
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}
