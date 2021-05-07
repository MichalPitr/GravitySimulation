#include "Game.h"

#include <iostream>
#include <cctype>
int main() {

    //initialize random seed
    srand(static_cast<unsigned>(time(0)));

    //initialize game object
    Game game;

    //Game loop
    while(game.running())
    {
        game.update();
        game.render();
    }
    //end of application
    return 0;
}
