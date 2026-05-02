/**
 * @file cw_returns.h
 * @brief Shared status and error codes for Craftworld.
 *
 * @details
 * This header defines the CW_Return enum, which gives the project one common
 * language for success, errors, and runtime states. Using named return codes is
 * clearer than returning unexplained numbers such as -1 or -302.
 *
 * For a beginner: a return code is a small value a function gives back to say
 * what happened. CW_OK means success. Negative values mean errors. Positive
 * values are normal game states such as pause or quit.
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

#ifndef RETURNS_H
#define RETURNS_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @enum CW_Return
 * @brief Project-wide result codes.
 *
 * @details
 * Codes are grouped by range so logs are easier to read:
 * - 0 means success.
 * - Negative values mean errors.
 * - Positive values mean non-error runtime states.
 */
typedef enum CW_Return {
    /** Successful operation. */
    CW_OK = 0,

    /** General failure when no more specific code is available. */
    CW_ERROR = -1,
    /** Unknown or unexpected failure. */
    CW_ERROR_UNKNOWN = -2,
    /** A function received an argument that is not valid. */
    CW_ERROR_INVALID_ARGUMENT = -3,
    /** A function received or produced a NULL pointer unexpectedly. */
    CW_ERROR_NULL_POINTER = -4,
    /** Memory allocation failed. */
    CW_ERROR_OUT_OF_MEMORY = -5,

    /** A required file could not be found. */
    CW_ERROR_FILE_NOT_FOUND = -100,
    /** A file existed but could not be read successfully. */
    CW_ERROR_FILE_READ_FAILED = -101,
    /** A file could not be written successfully. */
    CW_ERROR_FILE_WRITE_FAILED = -102,
    /** A game asset such as a texture, model, or sound failed to load. */
    CW_ERROR_ASSET_LOAD_FAILED = -103,
    /** A game asset could not be unloaded or released correctly. */
    CW_ERROR_ASSET_UNLOAD_FAILED = -104,

    /** The window failed during initialization. */
    CW_ERROR_WINDOW_INIT_FAILED = -200,
    /** raylib did not report the window as ready after creation. */
    CW_ERROR_WINDOW_NOT_READY = -201,
    /** Rendering failed. Reserved for future drawing/presentation errors. */
    CW_ERROR_RENDER_FAILED = -202,

    /** World creation failed. Reserved for future world-generation work. */
    CW_ERROR_WORLD_INIT_FAILED = -300,
    /** Player creation failed. Reserved for future player-system work. */
    CW_ERROR_PLAYER_INIT_FAILED = -301,
    /** Camera creation failed. */
    CW_ERROR_CAMERA_INIT_FAILED = -302,
    /** Input system creation failed. Reserved for future input setup work. */
    CW_ERROR_INPUT_INIT_FAILED = -303,

    /** Request to quit the game without treating it as an error. */
    CW_QUIT = 100,
    /** Request to restart the game/session. */
    CW_RESTART = 101,
    /** Runtime state indicating the game is paused. */
    CW_PAUSE = 102,
    /** Runtime state indicating the game should continue. */
    CW_CONTINUE = 103

} CW_Return;

/**
 * @brief Return true when a CW_Return value is an error.
 */
#define CW_FAILED(result) ((result) < 0)

/**
 * @brief Return true when a CW_Return value is success or a non-error state.
 */
#define CW_SUCCESS(result) ((result) >= 0)

#ifdef __cplusplus
}
#endif

#endif /* RETURNS_H */
