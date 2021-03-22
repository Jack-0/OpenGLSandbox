#define STB_IMAGE_IMPLEMENTATION
#include <std_image.h>

#include "Game.h"


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;


int main()
{
    if (game->init(WINDOW_WIDTH, WINDOW_HEIGHT) == -1)
        return -1;

    while ( game->running() )
    {
        game->handleEvents();
        game->update();
        game->render();
        game->calculate_fps();
    }

    game->clean();
    return 0;
}

