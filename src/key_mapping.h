/**
 * @file key_mapping.h
 * @brief Public input-mapping interface for Craftworld.
 *
 * @details
 * This header declares the function used to process project-specific keyboard
 * shortcuts. Keeping the declaration in a header lets main.c call the input
 * module without needing to know how each shortcut is implemented.
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

#ifndef KEY_MAPPING_H
#define KEY_MAPPING_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Short alias for processing the project's keyboard shortcuts.
 */
#define CW_KEY_MAP(c) (cw_key_mapping(c))

/**
 * @brief Process one frame of global keyboard shortcuts.
 */
extern void cw_key_mapping(Camera3D *c);

#ifdef __cplusplus
}
#endif

#endif /* KEY_MAPPING_H */
