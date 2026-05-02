/**
 * @file camera.h
 * @brief Public camera creation interface for Craftworld.
 *
 * @details
 * This header exposes the function used to create the game's default 3D camera.
 * Other source files include this header when they need a camera but do not
 * need to know every implementation detail of how the camera is configured.
 *
 * For a beginner: a header file is like a menu. It tells the rest of the
 * program what functions are available, while the .c file contains the actual
 * recipe.
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

#ifndef CAMERA_H
#define CAMERA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "raylib.h"

/**
 * @brief Short project-style alias for creating the default camera.
 *
 * @details
 * This macro keeps call sites compact while still routing the real work through
 * cw_camera_init(). If the camera creation process grows later, only the
 * function implementation needs to change.
 */
#define CW_CAMERA() (cw_camera_init())

/**
 * @brief Allocate and initialize the default 3D camera.
 *
 * @details
 * The caller receives ownership of the returned pointer. In plain language:
 * whoever asks for the camera is also responsible for freeing it later.
 *
 * @return A pointer to a Camera3D object on success, or NULL if allocation
 *         fails.
 */
extern Camera3D *cw_camera_init(void);

#ifdef __cplusplus
}
#endif

#endif /* CAMERA_H */
