#include "../inc/Board.hpp"
#include <iostream>

namespace  {

    constexpr char emptyField = ' ';
    constexpr char snakeSegment = 'X';
    constexpr char wallSegment = '#';
    constexpr char food = 'o';
    int x, y;
}

Board::Board(int w, int h):mWidth(w), mHeight(h), mBoard(mWidth, std::vector<char>(mHeight, emptyField))
{
}

void Board::printBoard(const int& frames, const int& score)
{
    std::cout<<"FRAMES: "<<frames<<"                           "<<"SCORE: "<<score<<std::endl;


    for(y = 0; y < mHeight; ++y)
    {
        for(x = 0; x < mWidth; ++x)
        {
            std::cout<<mBoard[x][y];
        }
        std::cout<<std::endl;
    }
}

void Board::removeSnakeTaileFromBoard(const Position& snakeTail)
{
    mBoard[snakeTail.x][snakeTail.y] = emptyField;
}

void Board::addSnakeInBoard(const std::vector<Position>& snakeBody)
{
    for(auto el : snakeBody)
    {
        mBoard[el.x][el.y] = snakeSegment;
    }
}

void Board::addFoodOnBoard(const Position& foodPos)
{
    mBoard[foodPos.x][foodPos.y] = food;
}

void Board::setUpWallInBoard()
{
    for(y = 0; y < mHeight; ++y)
    {
        for(x = 0; x < mWidth; ++x)
        {
            if(y == 0 or y == (mHeight-1) or x == 0 or x == (mWidth-1))
            {
                mBoard[x][y] = wallSegment;
            }
            else
            {
                mBoard[x][y] = emptyField;
            }
        }
    }
}

int Board::getWidth()
{
    return mWidth;
}

int Board::getHeight()
{
    return mHeight;
}
