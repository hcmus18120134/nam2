#pragma once

#include <iostream>
#include "utils.h"
#include "board.h"
using namespace std;

class board;
class rect
{
private:
    origin *o;
    resolution *s;
    align_type *type;
    // board *p;

public:
    string text;
    rect(int x, int y, int w, int h, string align_vertical, string align_horizontal)
    {
        o = new origin(x, y);
        s = new resolution(w, h);
        type = new align_type(align_vertical, align_horizontal);
    };
    rect(int x, int y, int w, int h)
    {
        o = new origin(x, y);
        s = new resolution(w, h);
        type = new align_type("middle", "center");
    };
    void clear();
    void update();
    ~rect()
    {
        delete o;
        delete s;
        delete type;
    }
};
void rect::clear()
{
    if (this->type->horizontal == "right")
    {
        for (int i = 0; i < this->s->w - 1; i++)
        {
            moveCursor(std::cout, this->o->x + this->s->w - 1 - i, this->o->y + this->s->h - 1);
            cout << ' ';
        }
    }
}
void rect::update()
{
    this->clear();
    // moveCursor(std::cout, this->o->x + this->s->w - 1, this->o->y + this->s->h - 1);
    if (this->type->horizontal == "right")
    {
        for (int i = 0; i < min(int(this->text.size()), this->s->w - 1); i++)
        {
            moveCursor(std::cout, this->o->x + this->s->w - 1 - i, this->o->y + this->s->h - 1);
            cout << this->text[this->text.size() - 1 - i];
        }
    }
}
