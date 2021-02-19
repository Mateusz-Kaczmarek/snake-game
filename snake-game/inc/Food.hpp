#pragma once
#include "Position.hpp"
#include <vector>

class Food
{
public:
   void drawNewFoodPos(const std::vector<Position>&, const Position&, const int&, const int&);
   bool isFoodToEat(const std::vector<Position>&);

   Position getFoodPos();
   void setFoodPos(Position newFoodPos);

private:
   Position mFoodPos;
};
