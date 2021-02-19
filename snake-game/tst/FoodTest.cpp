#include "gtest/gtest.h"
#include "Food.hpp"
#include "Position.hpp"
#include "vector"


class FoodTests : public ::testing::Test
{
protected:
    Food sut;
    std::vector<Position> snakeBody;
    Position snakeTail;
    int width;
    int height;

public:
    void SetUp() override
    {
        sut.setFoodPos({0,0});
        snakeBody = {{2,1},{2,2},{2,3}};
        snakeTail = {1,1};
        width = 5;
        height = 3;
    }
};

TEST_F(FoodTests, checkIfFoodNewPositionIsCorrect)
{
    sut.drawNewFoodPos(snakeBody, snakeTail, width, height);

    EXPECT_NE (0,  sut.getFoodPos().x);
    EXPECT_NE (0, sut.getFoodPos().y);
    EXPECT_NE ((width-1),  sut.getFoodPos().x);
    EXPECT_NE ((height-1),  sut.getFoodPos().y);

    if(snakeTail.x == sut.getFoodPos().x and snakeTail.y == sut.getFoodPos().y)
        EXPECT_NE (0,  1);


    for(auto el : snakeBody)
    {
        if(el.x == sut.getFoodPos().x and el.y == sut.getFoodPos().y)
            EXPECT_NE (0,  1);
    }
}

TEST_F(FoodTests, checkIfIsFoodToEat)
{
    sut.setFoodPos({2,3});
    bool isFoodToEat = sut.isFoodToEat(snakeBody);

    EXPECT_EQ(1, isFoodToEat);
}

struct FoodTestsParameters
{
    std::vector<Position> snakeBody;
    Position snakeTail;
    int width;
    int height;
};

class FoodTestsWithParameters : public ::testing::TestWithParam<FoodTestsParameters>
{
protected:
    Food sut;
};

TEST_P(FoodTestsWithParameters, checkIfFoodNewPositionIsCorrect)
{
    FoodTestsParameters testParam = GetParam();
    sut.drawNewFoodPos(testParam.snakeBody, testParam.snakeTail, testParam.width, testParam.height);

    EXPECT_NE (0,  sut.getFoodPos().x);
    EXPECT_NE (0, sut.getFoodPos().y);
    EXPECT_NE ((testParam.width-1),  sut.getFoodPos().x);
    EXPECT_NE ((testParam.height-1),  sut.getFoodPos().y);

    if(testParam.snakeTail.x == sut.getFoodPos().x and testParam.snakeTail.y == sut.getFoodPos().y)
        EXPECT_NE (0,  1);


    for(auto el : testParam.snakeBody)
    {
        if(el.x == sut.getFoodPos().x and el.y == sut.getFoodPos().y)
            EXPECT_NE (0,  1);
    }
}

INSTANTIATE_TEST_SUITE_P(TestSnakePos, FoodTestsWithParameters, ::testing::Values(
    FoodTestsParameters{ {{1,2},{1,3},{2,3}}, {1,1}, 6, 6},
    FoodTestsParameters{ {{2,6},{2,5},{2,4}}, {3,6}, 4, 8},
    FoodTestsParameters{ {{1,2},{1,1},{2,1},{3,1},{4,1}}, {2,2}, 6, 4} ));



