/**
 * @file raylib_init.c
 * @brief Creates the main raylib window and handles window-size shortcuts.
 *
 * @details
 * This file owns the early raylib setup for Craftworld. It sets the window
 * title, default size, minimum size, target frame rate, and a small group of
 * shortcuts for maximizing/restoring the window.
 *
 * For a beginner: raylib is the library that opens the game window and draws
 * graphics. This file is where the project tells raylib how the window should
 * behave.
 *
 * Copyright 2026 Craftworld contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "cw_returns.h"
#include "except.h"
#include "raylib.h"
#include "raymath.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Default width of the application window in pixels.
 */
static uint32_t raylib_width = 1280;

/**
 * @brief Default height of the application window in pixels.
 */
static uint32_t raylib_height = 720;

/**
 * @brief Smallest width allowed when the user resizes the window.
 */
static uint32_t raylib_min_width = 800;

/**
 * @brief Text displayed in the operating system's window title bar.
 */
static const char *raylib_main_win_title = "Craftworld";

/**
 * @brief Smallest height allowed when the user resizes the window.
 */
static uint32_t raylib_min_height = 600;

/**
 * @brief Initialize the main raylib window.
 *
 * @details
 * The function enables window resizing, opens the window, checks whether raylib
 * reports the window as ready, sets a minimum window size, and requests a target
 * frame rate of 60 frames per second.
 *
 * @return CW_OK when the window is ready, otherwise CW_ERROR_WINDOW_NOT_READY.
 */
CW_Return raylib_create_win(void) {

    /*
     * This flag must be set before InitWindow(). It tells raylib that the user
     * should be allowed to drag the window edges and resize the game.
     */
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(raylib_width, raylib_height, raylib_main_win_title);

    if (!IsWindowReady()) {
        CW_THROW(CW_ERROR_WINDOW_NOT_READY, "main window initialization failed.");
        return CW_ERROR_WINDOW_NOT_READY;
    }

    /*
     * A minimum size prevents the 3D viewport from becoming too tiny to use or
     * test comfortably.
     */
    SetWindowMinSize(raylib_min_width, raylib_min_height);

    SetTargetFPS(60);
    return CW_OK;
}

/**
 * @brief Process keyboard shortcuts that change the window size/mode.
 *
 * @details
 * F1 toggles between maximized and restored window states. Right Ctrl + F1
 * toggles raylib's borderless-windowed mode, which looks like fullscreen but
 * avoids switching the monitor display mode.
 *
 * @return CW_OK after the current frame's window shortcut handling completes.
 */
CW_Return raylib_win_resize_screen(void) {

    if (IsKeyDown(KEY_RIGHT_CONTROL) && IsKeyPressed(KEY_F1)) {
        ToggleBorderlessWindowed();
    } else if (IsKeyPressed(KEY_F1)) {
        if (IsWindowMaximized()) {
            RestoreWindow();
        } else {
            MaximizeWindow();
        }
    }

    return CW_OK;
}
