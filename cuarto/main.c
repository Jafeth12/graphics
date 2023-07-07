#include <stdio.h>
#include <stdlib.h>

#include "window.h"

int main(void) {
    window *win = win_create(800, 600, "Hello World", NULL);
    if (win == NULL) {
        fprintf(stderr, "Error creating window\n");
        return -1;
    }

    win_loop(win);
    win_destroy(win);

    return 0;
}
