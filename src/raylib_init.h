/**
 * @file raylib_init.h
 * @brief Public window lifecycle declarations for Craftworld.
 *
 * @details
 * This header exposes the functions and convenience macros used to create,
 * update, and close the raylib window. Source files include this header when
 * they need to interact with the project-level window setup without depending
 * on the implementation details inside raylib_init.c.
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

#ifndef RAYLIB_INIT_H
#define RAYLIB_INIT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "cw_returns.h"
#include "raylib.h"

/**
 * @brief Short alias for creating the main window.
 */
#define CREATE_WIN() (raylib_create_win())

/**
 * @brief Short alias for processing per-frame window resize shortcuts.
 */
#define RESIZE_WIN() (raylib_win_resize_screen())

/**
 * @brief Short alias for closing the raylib window.
 */
#define CLOSE_WIN() (CloseWindow())

/**
 * @brief Create the main raylib window.
 *
 * @return CW_OK on success, or a negative CW_Return error code on failure.
 */
extern CW_Return raylib_create_win(void);

/**
 * @brief Handle window-management shortcuts for one frame.
 *
 * @return CW_OK after shortcut processing completes.
 */
extern CW_Return raylib_win_resize_screen(void);

#ifdef __cplusplus
}
#endif

#endif /* RAYLIB_INIT_H */
