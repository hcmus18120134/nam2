#pragma once

#include <iostream>
#include "board.h"
#include "utils.h"
// win

#ifdef _WIN32
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#endif

// ubuntu

#ifdef __linux__
#define KEY_UP 65
#define KEY_DOWN 66
#define KEY_LEFT 68
#define KEY_RIGHT 67
#endif

#include "QEquation.h"
using namespace std;

class event
{
private:
    /* data */

public:
    static int px[6][4];
    static int py[6][4];
    static char table[6][4];
    event(/* args */);
    static bool isTriggered(); // return the key
    static char getkey(char x);
    ~event();
};
int event::py[6][4] = {
    {4, 4, 4, 4},
    {6, 6, 6, 6},
    {8, 8, 8, 8},
    {10, 10, 10, 10},
    {12, 12, 12, 12},
    {14, 14, 14, 14}};

int event::px[6][4] = {
    {38, 38, 38, 38},
    {5, 13, 22, 33},
    {5, 13, 22, 33},
    {5, 13, 22, 33},
    {5, 13, 22, 33},
    {5, 13, 22, 33}};

char event::table[6][4] = {
    {'=', '=', '=', '='},
    {'(', ')', '%', '!'},
    {'7', '8', '9', '/'},
    {'4', '5', '6', '*'},
    {'1', '2', '3', '-'},
    {'0', '.', '=', '+'}};
event::event(/* args */)
{
}
bool event::isTriggered()
{
    char c;
    char c2;
    board *scene = board::instance(40, 15); // singletons assign
    if (c = getch())
    {

        if (int(c) == 27) // get arrow key linux - 3bit
        {
            c = getch();
            c = getch();
            // cout << int(c);
            switch (int(c))
            {
            case KEY_UP:
                scene->cursor_x -= 1;
                break;
            case KEY_LEFT:
                scene->cursor_y -= 1;
                break;
            case KEY_DOWN:
                scene->cursor_x += 1;
                break;
            case KEY_RIGHT:
                scene->cursor_y += 1;
                break;
            }
        }
        if (int(c) == 10)
            c2 = table[scene->cursor_x][scene->cursor_y];
        else
            c2 = getkey(c);
        if (c2 != '=' && c2 != '!' && c2 != '@')
        {
            scene->text_box->text += c2;
            scene->ans_box->text = "ANS = 0" + scene->text_box->text;
            // add code here,
            // request equation string type is scene->text_box->text
            // return it to scene->ans_box->text

            // int res = CalEquation<int>(scene->text_box->text);
            // scene->ans_box->text = to_string(res);
        }
        if (c2 == '=')
        {
            scene->text_box->text = scene->ans_box->text.substr(5);
        }
        if (c2 == '!')
        {
            scene->text_box->text = "";
            scene->ans_box->text = "ANS = 0";
        }
        return 1;
    }
    return 0;
}
char event::getkey(char c)
{
    if (c >= '0' && c <= '9')
        return c;
    if (c == '+')
        return c;
    if (c == '-')
        return c;
    if (c == '*')
        return c;
    if (c == '/')
        return c;
    if (c == '=')
        return c;
    if (c == '.')
        return c;
    if (int(c) == 127)
        return '!';
    return '@';
}
event::~event()
{
}