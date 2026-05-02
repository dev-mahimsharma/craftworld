#include "cw_returns.h"
#include "raylib.h"
#include "raylib_init.h"

#include <stdio.h>
#include <stdlib.h>

int main() {

    CW_Return cw_create_window = CREATE_WIN();
    if (CW_FAILED(cw_create_window)) {
        exit(EXIT_FAILURE);
    }

    while (!WindowShouldClose()) {

        RESIZE_WIN();

        BeginDrawing();

        ClearBackground(BLUE);

        EndDrawing();
    }
    CLOSE_WIN();

    return 0;
}