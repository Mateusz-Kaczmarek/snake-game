#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <chrono>
#include <sys/ioctl.h>
#include <termios.h>

using namespace std;
using namespace std::chrono;

namespace
{

int bytesWaiting;
int position = 0;
int direction = 0;

void print(const int& max)
{
    for(int i=0; i<max;i++)
    {
        if(position == i)
        {
            cout<<"x";
        }
        else
        {
            cout<<" ";
        }
    }
    cout<<endl;
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
    int i = 0;
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

        print(20);
        sleepGame(1000);

        if(_kbhit())   /// If keyboard hit
        {
            char k;
            cin >> k; /// Character
            reactionOnKeyboard(k);
        }


        clearBoard();
        if(i == 20)
            i = 0;
    }
    return 0;
}

}//namespace
















