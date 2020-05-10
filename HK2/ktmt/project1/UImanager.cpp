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

    printf("\033c");                        // clear screen
    board *scene = board::instance(40, 15); // singletons assign
    scene->load("assets/demo.txt");         // load board
    scene->drawOnce();                      // draw board
    bool key;
    while (1)
    {
        // moveCursor(std::cout, 15, 40);
        if (key = event::isTriggered())
        {
            scene->update();
        }
    }
    return 0;
}