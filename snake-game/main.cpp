#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <chrono>
#include <sys/ioctl.h>
#include <termios.h>
#include <vector>

using namespace std;
using namespace std::chrono;

struct Position
{
    int x;
    int y;
};

enum class MoveDirection
{
    RIGHT,
    LEFT,
    UP,
    DOWN
};

int bytesWaiting;
int position = 0;
int x, y;

constexpr int width = 52;
constexpr int height = 22;
char board[width][height];
constexpr char wallSegment = '#';
constexpr char snakeSegment = 'X';
constexpr char food = 'o';
constexpr char emptyField = ' ';

Position snakeHead;
Position snakeTail;
MoveDirection direction = MoveDirection::RIGHT;

void updateTailPosition()
{
    if(board[snakeTail.x+1][snakeTail.y] == snakeSegment)
    {
      snakeTail.x += 1;
    }
    else if(board[snakeTail.x-1][snakeTail.y] == snakeSegment)
    {
      snakeTail.x -= 1;
    }
    else if(board[snakeTail.x][snakeTail.y+1] == snakeSegment)
    {
      snakeTail.y += 1;
    }
    else
    {
      snakeTail.y -= 1;
    }
}

void updateSnakePositionOnBoard()
{
    switch(direction)
    {
    case MoveDirection::RIGHT:
        snakeHead.x += 1;
        board[snakeHead.x][snakeHead.y] = snakeSegment;
        board[snakeTail.x][snakeTail.y] = emptyField;
        updateTailPosition();
        break;
    case MoveDirection::LEFT:
        snakeHead.x -= 1;
        board[snakeHead.x][snakeHead.y] = snakeSegment;
        board[snakeTail.x][snakeTail.y] = emptyField;
        updateTailPosition();
        break;
    case MoveDirection::UP:
        snakeHead.y -= 1;
        board[snakeHead.x][snakeHead.y] = snakeSegment;
        board[snakeTail.x][snakeTail.y] = emptyField;
        updateTailPosition();
        break;
    case MoveDirection::DOWN:
        snakeHead.y += 1;
        board[snakeHead.x][snakeHead.y] = snakeSegment;
        board[snakeTail.x][snakeTail.y] = emptyField;
        updateTailPosition();
        break;
    }
}

void setUpSnakeStartPosition()
{
    for(int i = 1; i < 4; ++i)
    {
        board[i][1] = snakeSegment;
    }

    snakeHead = {3,1};
    snakeTail = {1,1};
}

void setUpWallInBoard()
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

void printBoard()
{
    for(y = 0; y < height; ++y)
    {
        for(x = 0; x < width; ++x)
        {
            cout<<board[x][y];
        }
        cout<<endl;
    }
}

int _kbhit() {
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

    //int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

void sleepGame(int milliseconds)
{
    auto now = system_clock::now();
    system_clock::time_point timeEnd = now + duration<int, std::milli>(milliseconds);
    while (system_clock::now() < timeEnd)
    {
    }
}

void clearBoard()
{
    system("clear");
}

void reactionOnKeyboard(const char ch)
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

bool isNewDirectionValid(const char ch)
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
    setUpWallInBoard();
    setUpSnakeStartPosition();
    clearBoard();

    while (true)
    {
        printBoard();
        sleepGame(100);

        if(_kbhit())   /// If keyboard hit
        {
            char k;
            cin >> k; /// Character
            if(isNewDirectionValid(k))
            {
                reactionOnKeyboard(k);
            }
        }
        updateSnakePositionOnBoard();

        clearBoard();
    }

    return 0;
}


















