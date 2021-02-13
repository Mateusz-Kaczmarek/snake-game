#pragma once
#include <vector>
#include "Position.hpp"
#include "MoveDirection.hpp"


class Snake
{
public:
    void addNewSegmentToSnakeBody();
    void updateSnakeBody();
    void updateSnakePosition();
    void setUpSnakeStartPosition();

private:
    std::vector<Position> mSnakeBody;
    Position mSnakeTail;
    MoveDirection mDirection = MoveDirection::RIGHT;
};
