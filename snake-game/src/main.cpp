#include <iostream>
#include "../inc/Game.hpp"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <chrono>
#include <sys/ioctl.h>
#include <termios.h>
#include <vector>
#include <algorithm>

using namespace std;
using namespace std::chrono;

//struct Position
//{
//    int x;
//    int y;
//};

//enum class MoveDirection
//{
//    RIGHT,
//    LEFT,
//    UP,
//    DOWN
//};

int bytesWaiting;
int x, y, score = 0, frames = 1;
int sleepTime = 200;
int nextLvl = 3;

constexpr int width = 52;
constexpr int height = 22;
char board[width][height];
constexpr char wallSegment = '#';
constexpr char snakeSegment = 'X';
constexpr char food = 'o';
constexpr char emptyField = ' ';
vector<Position> snakeBody;

Position snakeTail;
Position foodPos;
MoveDirection direction = MoveDirection::RIGHT;

void drawNewFoodPos() //Food
{
    bool isFoodOnSnakeBodyPosition = true;

    while (isFoodOnSnakeBodyPosition)
    {
        foodPos.x = rand() % (width - 1);
        foodPos.y = rand() % (height - 1); // to avoid food on wall

        for(auto it = snakeBody.begin(); it < snakeBody.end(); it++)
        {
            if(it->x == foodPos.x and it->y == foodPos.y)
            {
                continue;
            }
        }

        if(snakeTail.x == foodPos.x and snakeTail.y == foodPos.y)
        {
            continue;
        }

        if(foodPos.x == 0)
            foodPos.x += 1; // food can not be on wall

        if(foodPos.y == 0)
            foodPos.y += 1;

        isFoodOnSnakeBodyPosition = false;
    }
}

void addFoodOnBoard() //Board
{
    drawNewFoodPos();
    board[foodPos.x][foodPos.y] = food;
}

bool isFoodToEat() //Food
{
    return ( snakeBody.back().x == foodPos.x and snakeBody.back().y == foodPos.y );
}

void addNewSegmentToSnakeBody() //Snake
{
    snakeBody.push_back(snakeTail);
    std::rotate(snakeBody.rbegin(), snakeBody.rbegin() + 1, snakeBody.rend());
}

void updateSnakeBody() //Snake
{
    //we update all body move position by on exept head = last elemetn in vector
    for(auto it = snakeBody.begin() ; it < snakeBody.end()-1; it++)
    {
        *it = *(it+1);
    }
}

void addSnakeInBoard() //Board
{
    for(auto el : snakeBody)
    {
        board[el.x][el.y] = snakeSegment;
    }
}

bool isCollision() //Game
{
    auto head = snakeBody.back();

    if(head.y == 0 or head.y == (height-1) or head.x == 0 or head.x == (width-1))
    {
        return true;
    }

    //check in snake body if head exist more than once
    for(auto it = snakeBody.begin(); it < snakeBody.end()-1; it++)
    {
        if(it->x == head.x and it->y == head.y)
        {
            return true;
        }
    }

    return false;
}

void updateSnakePosition() //Snake
{
    snakeTail = snakeBody.front();
    updateSnakeBody();

    switch(direction)
    {
    case MoveDirection::RIGHT:      
        snakeBody.back().x += 1;
        break;
    case MoveDirection::LEFT:
        snakeBody.back().x -= 1;
        break;
    case MoveDirection::UP:
        snakeBody.back().y -= 1;
        break;
    case MoveDirection::DOWN:
        snakeBody.back().y += 1;
        break;
    }
}

void removeSnakeTaileFromBoard() //Board
{
    board[snakeTail.x][snakeTail.y] = emptyField;
}

void setUpSnakeStartPosition() //Snake
{
    for(int i = 1; i < 4; ++i)
    {
        snakeBody.push_back({i,1});
    }
    addSnakeInBoard();
}

void setUpWallInBoard() //Board
{
    for(y = 0; y < height; ++y)
    {
        for(x = 0; x < width; ++x)
        {
            if(y == 0 or y == (height-1) or x == 0 or x == (width-1))
            {
                board[x][y] = wallSegment;
            }
            else
            {
                board[x][y] = emptyField;
            }
        }
    }
}

void printBoard() //Board
{
    cout<<"FRAMES: "<<frames<<"                           "<<"SCORE: "<<score<<endl;
    for(y = 0; y < height; ++y)
    {
        for(x = 0; x < width; ++x)
        {
            cout<<board[x][y];
        }
        cout<<endl;
    }
}

int _kbhit() //Game
{
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

void sleepGame(int milliseconds) //Game
{
    auto now = system_clock::now();
    system_clock::time_point timeEnd = now + duration<int, std::milli>(milliseconds);
    while (system_clock::now() < timeEnd)
    {
    }
}

void clearScreen() //Game
{
    system("clear");
}

void reactionOnKeyboard(const char ch) //Game
{
    switch (ch)
    {
        case 'j':
            direction = MoveDirection::LEFT;
            break;

        case 'l':
            direction = MoveDirection::RIGHT;
            break;

        case 'i':
            direction = MoveDirection::UP;
            break;

        case 'k':
            direction = MoveDirection::DOWN;
            break;

        default:
            break;
    }
}

bool isNewDirectionValid(const char ch) //Game
{
    bool valid = true;
    switch (ch)
    {
        case 'j':
            if(direction == MoveDirection::RIGHT)
                valid = false;
            break;

        case 'l':
            if(direction == MoveDirection::LEFT)
                valid = false;
            break;

        case 'i':
            if(direction == MoveDirection::DOWN)
                valid = false;
            break;

        case 'k':
            if(direction == MoveDirection::UP)
                valid = false;
            break;

        default:
            break;
    }

    return valid;
}

int main()
{
//    srand(time(NULL));
//    setUpWallInBoard();
//    setUpSnakeStartPosition();
//    addFoodOnBoard();
//    clearScreen();

//    while (true)
//    {
//        if(score != 0 and score == nextLvl and sleepTime > 20)
//        {
//            nextLvl += 3;
//            sleepTime -= 10;
//        }
//        printBoard();
//        sleepGame(sleepTime);

//        if(_kbhit())   /// If keyboard hit
//        {
//            char k;
//            cin >> k; /// Character
//            if(isNewDirectionValid(k))
//            {
//                reactionOnKeyboard(k);
//            }
//        }

//        updateSnakePosition();

//        if(isFoodToEat())
//        {
//            addFoodOnBoard();
//            addNewSegmentToSnakeBody();
//            score++;
//        }
//        else
//        {
//            removeSnakeTaileFromBoard();
//        }

//        addSnakeInBoard();

//        if(isCollision())
//        {
//            break;
//        }

//        clearScreen();
//        frames++;
//    }

//    cout<<"                    GAME OVER"<<endl;
//    cout<<"                   YOUR SCORE: "<<score<<endl;


    Game game;
    game.startGame();


    return 0;
}


















