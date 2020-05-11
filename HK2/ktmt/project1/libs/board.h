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
        text_box = new rect(1, 4, w - 2, 1, "middle", "right");
        ans_box = new rect(1, 2, w - 2, 1, "middle", "right");
    }
    // rect *data[10];

public:
    int cursor_x;
    int cursor_y;
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
        this->cursor_y = 0;
        this->cursor_x = 0;
        for (int i = 0; i < this->s->h; i++)
            for (int j = 0; j < this->s->w; j++)
            {
            }
    }
    void update()
    {
        this->cursor_y = min(this->cursor_y, 3);
        this->cursor_y = max(this->cursor_y, 0);
        this->cursor_x = min(this->cursor_x, 5);
        this->cursor_x = max(this->cursor_x, 0);
        this->text_box->update();
        this->ans_box->update();

        // for (int i = 0; i < buttons.size(); i++)
        // {
        //     buttons[i]->update();
        // }
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

#ifdef __linux__
    printf("\033c");
#endif
    moveCursor(std::cout, 0, 0);
    for (int i = 0; i < MAX_ROW; i++)
    {
        cout << data[i];
        cout << '\n';
    }
    cout << "calculator size: (" << this->s->h << ", " << this->s->w << ")" << endl;
}
