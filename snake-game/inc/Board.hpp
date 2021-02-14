#pragma once
#include "Position.hpp"
#include <vector>

class Board
{
public:
    Board(int w = 52, int h = 22):mWidth(w), mHeight(h)
    {
        mBoard[mWidth][mHeight];
    }
    void printBoard(const int&, const int&);
    void removeSnakeTaileFromBoard(const Position&);
    void addSnakeInBoard(const std::vector<Position>&);
    void addFoodOnBoard(const Position&);
    void setUpWallInBoard();

    int getWidth();
    int getHeight();

private:
    int mWidth;
    int mHeight;
    char mBoard[1][1];
};
