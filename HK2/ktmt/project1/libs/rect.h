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
    void update();
    ~rect()
    {
        delete o;
        delete s;
        delete type;
    }
};

void rect::update()
{
}
