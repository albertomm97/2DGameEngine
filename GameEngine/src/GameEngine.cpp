#include <iostream>
#include "./Game/Game.h"
#define SDL_MAIN_HANDLED

int main(int argc, char* argv[])
{
    Game game;

    game.Initialize();
    game.Run();
    game.Destroy();

    return 0;
}