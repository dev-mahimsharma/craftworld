/**
 * @file key_mapping.c
 * @brief Handles Craftworld keyboard shortcuts that are not built into raylib.
 *
 * @details
 * This file is the central place for project-specific input bindings. Movement
 * and mouse-look are handled by raylib's UpdateCamera() function in main.c, so
 * this file focuses on global shortcut keys such as showing or hiding the mouse
 * cursor.
 *
 * For a beginner: a key mapping connects a keyboard key to an action. For
 * example, "when F2 is pressed, show or hide the cursor."
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

/**
 * @brief Process global project keyboard shortcuts for the current frame.
 *
 * @details
 * This function should be called once per frame from the main loop. It checks
 * whether specific keys were pressed during this frame and performs the
 * matching action.
 */
void cw_key_mapping(void) {

    /*
     * F2 toggles cursor visibility. This is useful while testing first-person
     * controls because the cursor is normally hidden/captured during play.
     */
    if (IsKeyPressed(KEY_F2)) {
        if (IsCursorHidden()) {
            ShowCursor();
        } else {
            HideCursor();
        }
    }
}
