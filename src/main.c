#include <stdio.h>
#include <stdlib.h>

#include "game.h"

int main(void) {
    game *g = game_init();
    if (!g) {
        fprintf(stderr, "Error creating game\n");
        return -1;
    }

    game_run(g);
    game_destroy(g);

    return 0;
}
