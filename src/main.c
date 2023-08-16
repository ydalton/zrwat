#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "log.h"

#define W_WIDTH 800
#define W_HEIGHT 600
#define W_NAME "Tabak Zrwat"

unsigned int event_handler(SDL_Event *ev)
{
    unsigned int should_quit = 0;

    switch(ev->type) {
        case SDL_QUIT:
            should_quit = 1;
            break;
    }
    return should_quit;
}

int main(int argc, char **argv)
{
    SDL_Window *win;

    LOG_I("Command line: argc = %d, invoked name: %s\n", argc, argv[0]);

    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        LOG_E("SDL failed to initialise: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    win = SDL_CreateWindow(W_NAME,
                           SDL_WINDOWPOS_UNDEFINED,
                           SDL_WINDOWPOS_UNDEFINED,
                           W_WIDTH,
                           W_HEIGHT,
                           SDL_WINDOW_OPENGL);
    if(!win) {
        LOG_E("Cannot create window: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    while(1) {
        SDL_Event ev;
        SDL_PollEvent(&ev);
        if(event_handler(&ev))
            break;
    }

    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
