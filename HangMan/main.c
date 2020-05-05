#include <stdio.h>
#include "dictio.c"
#include "game.c"

#define T_MAX_WORD 100

int main() {
    run();
    printf("\n\nPress a key to exit.\n");
    scanf("%c");
    return 0;
}
