#pragma once

class Board
{
public:
    Board(int w = 52, int h = 22):width(w), height(h)
    {
        board[width][height];
    }
    void printBoard();
    void removeSnakeTaileFromBoard();
    void addSnakeInBoard();
    void setUpWallInBoard();
    void reactionOnKeyboard(const char ch);
    bool isNewDirectionValid(const char ch);
private:
    const int width;
    const int height;
    char board[1][1];
};
