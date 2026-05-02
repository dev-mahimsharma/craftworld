/**
 * @file main.c
 * @brief Program entry point and main game loop for Craftworld.
 *
 * @details
 * This file controls the lifetime of the application. It creates the window,
 * initializes the camera, runs the frame-by-frame loop, draws a simple 3D scene,
 * and releases resources before the program exits.
 *
 * For a person who is new to coding: main.c is the starting line of the
 * program. The operating system calls main(), and from there the game keeps
 * repeating a loop: read input, update the camera, draw the scene, then do it
 * again until the window is closed.
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

#include "camera.h"
#include "cw_returns.h"
#include "key_mapping.h"
#include "raylib.h"
#include "raylib_init.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Start Craftworld, run the render loop, and shut the program down.
 *
 * @details
 * The function is intentionally small and high level. It does not contain the
 * full implementation of window creation, camera creation, or input mapping.
 * Instead, it calls modules that own those jobs. This makes the program easier
 * to understand because main() reads like a sequence of major steps.
 *
 * @return EXIT_SUCCESS when the game closes normally, or EXIT_FAILURE when a
 *         required startup step fails.
 */
int main(void) {

    /*
     * The window must exist before raylib can draw anything. CREATE_WIN()
     * returns a project status code so startup failures can be detected cleanly.
     */
    CW_Return cw_create_window = CREATE_WIN();
    if (CW_FAILED(cw_create_window)) {
        return EXIT_FAILURE;
    }

    /*
     * Hide and capture the mouse cursor. First-person games usually do this so
     * moving the mouse rotates the camera instead of moving a desktop pointer.
     */
    DisableCursor();

    /*
     * Create the camera used for rendering the 3D world. The pointer is checked
     * before use because memory allocation can fail on any real system.
     */
    Camera3D *camera = CW_CAMERA();
    if (camera == NULL) {
        fprintf(stderr, "camera allocation failed\n");
        CLOSE_WIN();
        return EXIT_FAILURE;
    }

    /*
     * Main game loop.
     *
     * WindowShouldClose() becomes true when the user closes the window or uses
     * raylib's close shortcut. Until that happens, the body of this loop runs
     * once per frame.
     */
    while (!WindowShouldClose()) {
        /*
         * Handle window shortcut keys and project-specific key mappings before
         * drawing. This keeps user actions responsive.
         */
        RESIZE_WIN();
        CW_KEY_MAP();

        /*
         * raylib updates the first-person camera from keyboard and mouse input.
         * By default this provides movement such as WASD and mouse-look.
         */
        UpdateCamera(camera, CAMERA_FIRST_PERSON);

        /*
         * BeginDrawing() and EndDrawing() wrap all 2D/3D drawing for one frame.
         * Anything drawn between them becomes visible on the screen.
         */
        BeginDrawing();
        ClearBackground(BLUE);

        /*
         * BeginMode3D() tells raylib that following draw calls should use the
         * camera's 3D perspective instead of flat 2D screen coordinates.
         */
        BeginMode3D(*camera);
        DrawGrid(20, 1.0f);
        DrawCube((Vector3){0, 0.5f, 0}, 1, 1, 1, BROWN);
        EndMode3D();

        EndDrawing();
    }

    /*
     * Release resources in the reverse order of creation: close the window and
     * free the camera memory before returning to the operating system.
     */
    CLOSE_WIN();
    MemFree(camera);

    return EXIT_SUCCESS;
}
