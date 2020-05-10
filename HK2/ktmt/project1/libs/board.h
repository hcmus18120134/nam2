#pragma once

#include <iostream>
#include "rect.h"
#include "utils.h"

#define pb push_back
#define MAX_ROW 15
#define MAX_COL 40

using namespace std;
class board
{
    //singleton
private:
    resolution *s;
    vector<rect *> buttons;

    static board *p;
    string data[MAX_ROW];

private:
    board(int w, int h)
    {
        s = new resolution(w, h);
        text_box = new rect(1, 1, w - 2, 1, "middle", "right");
        ans_box = new rect(3, 1, w - 2, 1, "middle", "right");
    }
    // rect *data[10];

public:
    rect *ans_box;
    rect *text_box;
    static board *instance(int w, int h)
    {
        if (!p)
            p = new board(w, h);

        return p;
    }
    void load(string path)
    {
        // default size is 34 15
        string line;
        ifstream myfile(path);
        if (myfile.is_open())
        {
            for (int i = 0; i < MAX_ROW; i++)
            {
                getline(myfile, data[i]);
            }
            myfile.close();
        }
        else
            cout << "Unable to open file\n";
    }

    void reset()
    {
        for (int i = 0; i < this->s->h; i++)
            for (int j = 0; j < this->s->w; j++)
            {
            }
    }
    void update()
    {
        for (int i = 0; i < buttons.size(); i++)
        {
            buttons[i]->update();
        }
    }
    void drawOnce();
    ~board()
    {
        delete s;
        for (int i = 0; i < buttons.size(); i++)
        {
            delete buttons[i];
        }
    }
};

board *board::p = NULL;

void board::drawOnce()
{
    for (int i = 0; i < MAX_ROW; i++)
    {
        cout << data[i];
        cout << '\n';
    }
    cout << "calculator size: (" << this->s->h << ", " << this->s->w << ")" << endl;
}
