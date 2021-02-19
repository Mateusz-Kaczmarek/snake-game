#pragma once
#include "Position.hpp"
#include <vector>

class Board
{
public:
    Board();
    Board(int, int);
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
    std::vector<std::vector<char>> mBoard;
};
