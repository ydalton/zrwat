#ifndef ZRWAT_H_
#define ZRWAT_H_

#include <SDL2/SDL.h>

#define W_WIDTH 800
#define W_HEIGHT 600
#define W_NAME "Tabak Zrwat"

struct game {
    const char *name;
    int width, height;
    SDL_Window *win;
};

int zrwat_init(struct game *g);
unsigned int zrwat_event_handler(SDL_Event *ev);
void zrwat_loop();
void zrwat_end(struct game *g);

#endif
