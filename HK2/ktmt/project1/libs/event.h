#pragma once

#include <iostream>
#include "board.h"
#include "utils.h"
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;

class event
{
private:
    /* data */
public:
    event(/* args */);
    static bool isTriggered(); // return the key
    static char getkey(char x);
    ~event();
};

event::event(/* args */)
{
}
bool event::isTriggered()
{
    char c;
    board *scene = board::instance(40, 15); // singletons assign
    if (c = getch())
    {
        c = getkey(c);
        // cout << c;
        if (c != '=' && c != '!')
        {
            scene->text_box->text += c;
        }
        if (c == '=')
            scene->text_box->text = scene->ans_box->text;
        if (c == '!')
            scene->text_box->text = "";

        return 1;
    }
    return 0;
}
char event::getkey(char c)
{
    if (c > '0' && c < '9')
        return c;
    if (c == '+')
        return c;
    if (c == '-')
        return c;
    if (c == '*')
        return c;
    if (c == '/')
        return c;
    if (int(c) == 10 || c == '=')
        return '=';
    if (int(c) == 127)
        return '!';
    return '@';
}
event::~event()
{
}