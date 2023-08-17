#include <GL/glew.h>

#include "zrwat.h"
#include "log.h"

int zrwat_init(struct game *g)
{

    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        LOG_E("SDL failed to initialise: %s\n", SDL_GetError());
        return -1;
    }

    g->win = SDL_CreateWindow(g->name,
                           SDL_WINDOWPOS_UNDEFINED,
                           SDL_WINDOWPOS_UNDEFINED,
                           g->width,
                           g->height,
                           SDL_WINDOW_OPENGL);
    if(!g->win) {
        LOG_E("Cannot create window: %s\n", SDL_GetError());
        return -1;
    }

    SDL_GL_CreateContext(g->win);

    if(glewInit() != GLEW_OK) {
        LOG_E("Cannot initialize GLEW! %s", "");
        return -1;
    }

    glViewport(0, 0, g->width, g->height);

    return 0;
}


unsigned int zrwat_event_handler(SDL_Event *ev)
{
    unsigned int should_quit = 0;

    switch(ev->type) {
        case SDL_QUIT:
            should_quit = 1;
            break;
    }
    return should_quit;
}

void zrwat_render(struct game *g)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(g->win);
}

void zrwat_loop(struct game *g)
{
    while(1) {
        SDL_Event ev;
        SDL_PollEvent(&ev);
        if(zrwat_event_handler(&ev))
            return;
        zrwat_render(g);
    }
}

void zrwat_end(struct game *g)
{
    SDL_DestroyWindow(g->win);
    SDL_Quit();
}
