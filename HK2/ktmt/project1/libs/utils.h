#pragma once
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}
class resolution
{
public:
    int w;
    int h;
    resolution(int pw, int ph)
    {
        w = pw;
        h = ph;
    }
};

class origin
{
public:
    int y;
    int x;
    origin(int px, int py)
    {
        x = px;
        y = py;
    }
};

class align_type
{
public:
    string vertical;   // top - middle - bottom
    string horizontal; // left - center - right

    align_type(string align_vertical, string align_horizontal)
    {
        vertical = align_vertical;
        horizontal = align_horizontal;
    }
};

void moveCursor(std::ostream &os, int row, int col)
{
    os << "\033[" << col << ";" << row << "H";
}