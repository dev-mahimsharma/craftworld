/**
 * @file camera.c
 * @brief Creates and configures the default 3D camera used by Craftworld.
 *
 * @details
 * This source file contains the implementation for the camera factory declared
 * in camera.h. A camera in raylib describes where the player is looking from,
 * what point the player is looking at, which direction is considered "up", and
 * how wide the field of view should be.
 *
 * For a person who is new to programming: think of this file as the place where
 * the game's "eyes" are created. The camera is what decides what part of the 3D
 * world appears on the screen.
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
#include "except.h"
#include "raylib.h"

#include <stdlib.h>

/**
 * @brief Allocate and initialize the game's default 3D camera.
 *
 * @details
 * The returned camera starts above the ground and looks toward the center of
 * the simple test scene. This makes the grid and cube visible immediately when
 * the program opens. The camera uses raylib's perspective projection, which is
 * the normal 3D view where far objects appear smaller than nearby objects.
 *
 * Memory for the camera is allocated with raylib's MemAlloc function. That
 * means the caller owns the returned pointer and must release it with MemFree
 * when the game shuts down.
 *
 * @return A pointer to a fully initialized Camera3D object. Returns NULL if
 *         memory allocation fails.
 */
Camera3D *cw_camera_init(void) {

    Camera3D *cw_camera = MemAlloc(sizeof(Camera3D));
    if (cw_camera == NULL) {
        CW_THROW(CW_ERROR_CAMERA_INIT_FAILED, "failed to initialize memory for camera.\n");
        return NULL;
    }

    /*
     * position:
     *     The place where the camera is standing in the 3D world.
     *
     * target:
     *     The point the camera initially looks toward.
     *
     * up:
     *     The direction considered upward. A positive Y value matches the
     *     common convention that "up" in the world is along the Y axis.
     */
    cw_camera->position = (Vector3){0.0f, 2.0f, 6.0f};
    cw_camera->target = (Vector3){0.0f, 1.0f, 0.0f};
    cw_camera->up = (Vector3){0.0f, 1.0f, 0.0f};

    /*
     * fovy is the vertical field of view in degrees. Larger values show more
     * of the world but can feel stretched; 60 degrees is a common comfortable
     * starting point for first-person cameras.
     */
    cw_camera->fovy = 60.0f;
    cw_camera->projection = CAMERA_PERSPECTIVE;

    return cw_camera;
}
