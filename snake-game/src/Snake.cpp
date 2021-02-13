#include "../inc/Snake.hpp"
#include <algorithm>

namespace
{
unsigned int nextElement = 1;
int startPos = 1;
int startPosLimit = 4;

}

    void Snake::addNewSegmentToSnakeBody()
    {
        mSnakeBody.push_back(mSnakeTail);
        std::rotate(mSnakeBody.rbegin(), mSnakeBody.rbegin() + 1, mSnakeBody.rend());
    }

    void Snake::updateSnakeBody()
    {
        //we update all body move position by on exept head = last elemetn in vector
        for(auto it = mSnakeBody.begin() ; it < mSnakeBody.end() - 1; it++)
        {
            *it = *(it + nextElement);
        }
    }

    void Snake::updateSnakePosition()
    {
        mSnakeTail = mSnakeBody.front();
        updateSnakeBody();

        switch(mDirection)
        {
        case MoveDirection::RIGHT:
            mSnakeBody.back().x += 1;
            break;
        case MoveDirection::LEFT:
            mSnakeBody.back().x -= 1;
            break;
        case MoveDirection::UP:
            mSnakeBody.back().y -= 1;
            break;
        case MoveDirection::DOWN:
            mSnakeBody.back().y += 1;
            break;
        }
    }

    void Snake::setUpSnakeStartPosition()
    {
        for(int i = 1; i < startPosLimit; ++i)
        {
            mSnakeBody.push_back({i,startPos});
        }

        //addSnakeInBoard() - remember
    }


