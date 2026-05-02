/**
 * @file except.h
 * @brief Public diagnostic logging interface for Craftworld.
 *
 * @details
 * This header declares the logging helper and convenience macros used to report
 * errors with useful source-location information. The macros automatically pass
 * the current file name and line number, which saves typing and makes every log
 * message easier to trace.
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

#ifndef EXCEPT_H
#define EXCEPT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "cw_returns.h"

/**
 * @brief Print a structured diagnostic message.
 *
 * @param code Project status/error code associated with the message.
 * @param file Source file name to show in the log.
 * @param line Source line number to show in the log.
 * @param fmt  printf-style message format.
 * @param ...  Optional values used by the format string.
 */
void cw_except_raise(CW_Return code, const char *file, int line, const char *fmt, ...);

/**
 * @brief Report a problem and automatically include the current file and line.
 */
#define CW_THROW(code, fmt, ...) cw_except_raise(code, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

/**
 * @brief Log a message if a condition is false.
 *
 * @details
 * This macro behaves like a lightweight assertion logger. It reports the
 * problem but does not stop the program by itself. The surrounding code should
 * still return, recover, or exit when that is required.
 */
#define CW_ASSERT(cond, code, fmt, ...)                                                            \
    do {                                                                                           \
        if (!(cond)) {                                                                             \
            cw_except_raise(code, __FILE__, __LINE__, fmt, ##__VA_ARGS__);                         \
        }                                                                                          \
    } while (0)

#ifdef __cplusplus
}
#endif

#endif /* EXCEPT_H */
