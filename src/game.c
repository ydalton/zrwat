#include "log.h"
#include "game.h"

struct zrwat_game game_init()
{
    struct zrwat_game game;
    game.card_ptr = game.cards + ZRWAT_NUMBER_CARDS;
    LOG_I("%p", (void *) game.card_ptr);
    return game;
}

void game_logic(struct zrwat_game *zg)
{
    LOG_I("%d\n", POT_ELEVEN);
    LOG_I("%p\n", (void *) zg->card_ptr);
}
