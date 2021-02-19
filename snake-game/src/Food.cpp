#include "../inc/Food.hpp"
#include <time.h>
#include <stdlib.h>

void Food::drawNewFoodPos(const std::vector<Position>& snakeBody, const Position& snakeTail, const int& width, const int& height)
{
    bool isFoodOnSnakeBodyPosition = true;

    while (isFoodOnSnakeBodyPosition)
    {
        srand(time(NULL));
        mFoodPos.x = rand() % (width - 1);
        mFoodPos.y = rand() % (height - 1); // to avoid food on wall

        if(mFoodPos.x == 0)
            ++mFoodPos.x; // food can not be on wall

        if(mFoodPos.y == 0)
            ++mFoodPos.y;

        if(snakeTail.x == mFoodPos.x and snakeTail.y == mFoodPos.y)
        {
            continue;
        }

        for(auto el : snakeBody)
        {
            if(el.x == mFoodPos.x and el.y == mFoodPos.y)
            {
                continue;
            }
        }

        isFoodOnSnakeBodyPosition = false;
    }
}

bool Food::isFoodToEat(const std::vector<Position>& snakeBody)
{
    return ( snakeBody.back().x == mFoodPos.x and snakeBody.back().y == mFoodPos.y );
}

Position Food::getFoodPos()
{
    return mFoodPos;
}

void Food::setFoodPos(Position newFoodPos)
{
    mFoodPos = newFoodPos;
}
