#pragma once
#include "Position.hpp"

class Food
{
public:
   void drawNewFoodPos();
   void addFoodOnBoard();
   bool isFoodToEat();

private:
   Position foodPos;
};
