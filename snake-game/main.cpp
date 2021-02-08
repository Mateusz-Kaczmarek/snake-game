#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <chrono>
#include <sys/ioctl.h>
#include <termios.h>
#include <vector>

using namespace std;
using namespace std::chrono;

int bytesWaiting;
int position = 0;
int direction = 0;
int x, y;

constexpr int width = 52;
constexpr int height = 22;
constexpr char block = '#';
constexpr char snakeSegment = 'X';
constexpr char food = 'o';

struct Position
{
    int x;
    int y;
};

Position snakeHead;
vector<Position> snakeBody;

void setSnakeStartPosition()
{
    snakeHead.x = 3;
    snakeHead.y = 1;

    for(int i = 1; i < 4; ++i)
    {
        snakeBody.push_back(Position{i,1});
    }
}

bool isWall(const int& x, const int& y)
{
    if(y == 0 or y == (height-1) or x == 0 or x == (width-1))
    {
        return true;
    }

    return false;
}

bool isSnakeBody(const int& x, const int& y)
{
    for(auto seg : snakeBody)
    {
         if(seg.x == x and seg.y == y)
         {
             return true;
         }
    }

    return false;
}



void printBoard()
{
    for(y = 0; y < height; ++y)
    {
        for(x = 0; x < width; ++x)
        {
            if(isWall(x, y))
            {
                cout<<block;
            }
            else
            {
                if(isSnakeBody(x, y))
                {
                    cout<<snakeSegment;
                }
//                else if(isFood(x, y))
//                {
//                    cout<<food;
//                }
                else
                {
                    cout<<' ';
                }
            }
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
            direction = 1;
            break;

        case 'l':
            direction = 0;
            break;

        default:
            break;
    }
}

int main()
{
    setSnakeStartPosition();

    while (true)
    {
        if(!direction)
        {
            if(position < 20)
                ++position;
        }
        else
        {
            if(position > 0)
                --position;
        }

        printBoard();
        sleepGame(1000);

        if(_kbhit())   /// If keyboard hit
        {
            char k;
            cin >> k; /// Character
            reactionOnKeyboard(k);
        }


        clearBoard();
    }

    return 0;
}


















