#include <iostream>
#include <stdlib.h>
#include "libs/board.h"
#include "libs/event.h"
#include "libs/utils.h"
using namespace std;

class UImanager
{
private:
public:
    UImanager(/* args */){};
};

int main()
{

#ifdef __linux__
    printf("\033c");
#endif
    // clear screen
    board *scene = board::instance(40, 15); // singletons assign
    scene->load("assets/demo.txt");         // load board
    scene->reset();
    scene->drawOnce(); // draw board
    bool key;
    while (1)
    {
        // debug cursor
        // moveCursor(std::cout, 17, 1);
        // cout << scene->cursor_x << ' ' << scene->cursor_y;
        // cout << event::table[scene->cursor_x][scene->cursor_y];
        moveCursor(std::cout, event::px[scene->cursor_x][scene->cursor_y], event::py[scene->cursor_x][scene->cursor_y]);
        if (key = event::isTriggered())
        {
            scene->drawOnce(); // draw board
            scene->update();
        }
    }
    return 0;
}