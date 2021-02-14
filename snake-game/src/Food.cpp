#include "../inc/Food.hpp"
#include <time.h>
#include <stdlib.h>

namespace
{
    bool isFoodOnSnakeBodyPosition = true;

}
void Food::drawNewFoodPos(const std::vector<Position>& snakeBody, const Position& snakeTail, const int& width, const int& height)
{
    srand(time(NULL));

    while (isFoodOnSnakeBodyPosition)
    {
        mFoodPos.x = rand() % (width - 1);
        mFoodPos.y = rand() % (height - 1); // to avoid food on wall

        for(auto it = snakeBody.begin(); it < snakeBody.end(); it++)
        {
            if(it->x == mFoodPos.x and it->y == mFoodPos.y)
            {
                continue;
            }
        }

        if(snakeTail.x == mFoodPos.x and snakeTail.y == mFoodPos.y)
        {
            continue;
        }

        if(mFoodPos.x == 0)
            mFoodPos.x += 1; // food can not be on wall

        if(mFoodPos.y == 0)
            mFoodPos.y += 1;

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
