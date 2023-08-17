#include <stdlib.h>

#include "zrwat.h"
#include "log.h"

int main(int argc, char **argv)
{
    LOG_I("Command line: argc = %d, invoked name: %s\n", argc, argv[0]);

    struct game zrwat;

    zrwat.width = W_WIDTH;
    zrwat.height = W_HEIGHT;
    zrwat.name = W_NAME;

    if(zrwat_init(&zrwat) != 0) {
        LOG_E("Cannot initialize game: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    zrwat_loop(&zrwat);

    zrwat_end(&zrwat);

    return 0;
}
