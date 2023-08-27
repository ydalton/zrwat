#ifndef ZRWAT_H_
#define ZRWAT_H_

#include <SDL2/SDL.h>
#include "game.h"

#define W_WIDTH 800
#define W_HEIGHT 600
#define W_NAME "Tabak Zrwat"

#define BG_GRAY 0.4, 0.4, 0.4

struct game {
    const char *name;
    int width, height;
    SDL_Window *win;
    unsigned int program;
    struct zrwat_game zrwat;
};

int zrwat_init(struct game *);
/* unsigned int zrwat_event_handler(SDL_Event *ev); */
void zrwat_loop(struct game *);
void zrwat_end(struct game *);

#endif
