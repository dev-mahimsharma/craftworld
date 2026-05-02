#include "camera.h"
#include "cw_returns.h"
#include "key_mapping.h"
#include "raylib.h"
#include "raylib_init.h"

#include <stdio.h>
#include <stdlib.h>

int main() {

    // create main window

    CW_Return cw_create_window = CREATE_WIN();
    if (CW_FAILED(cw_create_window)) {
        exit(EXIT_FAILURE);
    }

    // this function disables cursor
    DisableCursor();

    // setup camera

    Camera3D *camera = CW_CAMERA();
    if (camera == NULL) {
        fprintf(stderr, "camera allocation failed\n");
        exit(EXIT_FAILURE);
    }

    while (!WindowShouldClose()) {

        // used to resize window
        RESIZE_WIN();

        // contains all the key_mappings of the game.
        CW_KEY_MAP();

        UpdateCamera(camera, CAMERA_FIRST_PERSON);  // create first person like camera
                                                    // configuration.

        BeginDrawing();

        ClearBackground(BLUE);

        BeginMode3D(*camera);

        DrawGrid(20, 1.0f);
        DrawCube((Vector3){0, 0.5f, 0}, 1, 1, 1, BROWN);

        EndMode3D();

        EndDrawing();
    }
    CLOSE_WIN();

    MemFree(camera);
    return 0;
}