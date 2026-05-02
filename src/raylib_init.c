#include "cw_returns.h"
#include "except.h"
#include "raylib.h"
#include "raymath.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t raylib_width = 1280;
static uint32_t raylib_height = 720;
static uint32_t raylib_min_width = 800;
static uint32_t raylib_min_height = 600;

static const char *raylib_main_win_title = "Craftworld";

CW_Return raylib_create_win(void) {

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);  // it allows/permits the window to resize.

    InitWindow(raylib_width, raylib_height, raylib_main_win_title);

    if (!IsWindowReady()) {
        CW_THROW(CW_ERROR_WINDOW_NOT_READY, "main window initialization failed.");
        return CW_ERROR_WINDOW_NOT_READY;  //-201
    }

    SetWindowMinSize(raylib_min_width, raylib_min_height);  // min size of window.

    SetTargetFPS(60);
    return CW_OK;
}

CW_Return raylib_win_resize_screen(void) {

    if (IsKeyDown(KEY_RIGHT_CONTROL) && IsKeyPressed(KEY_F1)) {
        // if multiple times f1 is pressed then toggle borderless window.
        ToggleBorderlessWindowed();
    }

    else if (IsKeyPressed(KEY_F1)) {
        if (IsWindowMaximized()) {
            RestoreWindow();
        } else {
            MaximizeWindow();
        }
    }

    CW_OK;
}