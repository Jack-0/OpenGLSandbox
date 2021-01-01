#define STB_IMAGE_IMPLEMENTATION
#include <std_image.h>

#include "Game.h"


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main()
{
    if (Game::Instance()->init(WINDOW_WIDTH, WINDOW_HEIGHT) == -1)
        return -1;

    while ( Game::Instance()->running() )
    {
        Game::Instance()->handleEvents();
        Game::Instance()->update();
        Game::Instance()->render();
        Game::Instance()->calculate_fps();
    }

    Game::Instance()->clean();
    return 0;
}

