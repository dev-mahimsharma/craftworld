/**
 * @file except.c
 * @brief Diagnostic logging implementation for Craftworld status codes.
 *
 * @details
 * This file turns project error/status codes into readable log messages. It is
 * not a C++ exception system. The name "except" here means "report an
 * exceptional situation" by printing useful debugging information to stderr.
 *
 * For a beginner: stderr is a special output stream normally shown in the
 * terminal. It is used for errors so normal program output and error output can
 * be separated.
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

#include "except.h"

#include <stdarg.h>
#include <stdio.h>
#include <time.h>

/**
 * @brief Convert a CW_Return value into a readable constant name.
 *
 * @details
 * Numeric error codes are useful for computers, but symbolic names are much
 * easier for people to understand. This helper keeps log output readable by
 * printing names such as CW_ERROR_WINDOW_NOT_READY instead of only -201.
 *
 * @param code The project status code that should be described.
 *
 * @return A string literal containing the symbolic name for the code. Unknown
 *         values return "CW_RETURN_UNKNOWN".
 */
static const char *cw_return_to_string(CW_Return code) {
    switch (code) {
        case CW_OK:
            return "CW_OK";

        case CW_ERROR:
            return "CW_ERROR";
        case CW_ERROR_UNKNOWN:
            return "CW_ERROR_UNKNOWN";
        case CW_ERROR_INVALID_ARGUMENT:
            return "CW_ERROR_INVALID_ARGUMENT";
        case CW_ERROR_NULL_POINTER:
            return "CW_ERROR_NULL_POINTER";
        case CW_ERROR_OUT_OF_MEMORY:
            return "CW_ERROR_OUT_OF_MEMORY";

        case CW_ERROR_FILE_NOT_FOUND:
            return "CW_ERROR_FILE_NOT_FOUND";
        case CW_ERROR_FILE_READ_FAILED:
            return "CW_ERROR_FILE_READ_FAILED";
        case CW_ERROR_FILE_WRITE_FAILED:
            return "CW_ERROR_FILE_WRITE_FAILED";
        case CW_ERROR_ASSET_LOAD_FAILED:
            return "CW_ERROR_ASSET_LOAD_FAILED";
        case CW_ERROR_ASSET_UNLOAD_FAILED:
            return "CW_ERROR_ASSET_UNLOAD_FAILED";

        case CW_ERROR_WINDOW_INIT_FAILED:
            return "CW_ERROR_WINDOW_INIT_FAILED";
        case CW_ERROR_WINDOW_NOT_READY:
            return "CW_ERROR_WINDOW_NOT_READY";
        case CW_ERROR_RENDER_FAILED:
            return "CW_ERROR_RENDER_FAILED";

        case CW_ERROR_WORLD_INIT_FAILED:
            return "CW_ERROR_WORLD_INIT_FAILED";
        case CW_ERROR_PLAYER_INIT_FAILED:
            return "CW_ERROR_PLAYER_INIT_FAILED";
        case CW_ERROR_CAMERA_INIT_FAILED:
            return "CW_ERROR_CAMERA_INIT_FAILED";
        case CW_ERROR_INPUT_INIT_FAILED:
            return "CW_ERROR_INPUT_INIT_FAILED";

        case CW_QUIT:
            return "CW_QUIT";
        case CW_RESTART:
            return "CW_RESTART";
        case CW_PAUSE:
            return "CW_PAUSE";
        case CW_CONTINUE:
            return "CW_CONTINUE";

        default:
            return "CW_RETURN_UNKNOWN";
    }
}

/**
 * @brief Print a structured diagnostic message to stderr.
 *
 * @details
 * The function prints a clear block containing the time, status code, source
 * file, source line, and custom message. It does not close the game or stop the
 * process. The caller decides whether the reported problem is fatal.
 *
 * @param code Project status/error code associated with the problem.
 * @param file Source file where the problem was reported, usually __FILE__.
 * @param line Source line where the problem was reported, usually __LINE__.
 * @param fmt  printf-style format string for the human-readable message.
 * @param ...  Optional values used by the format string.
 */
void cw_except_raise(CW_Return code, const char *file, int line, const char *fmt, ...) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    fprintf(stderr, "\n================ EXCEPTION ================\n");

    if (t != NULL) {
        fprintf(stderr, "[%02d:%02d:%02d]\n", t->tm_hour, t->tm_min, t->tm_sec);
    }

    fprintf(stderr, "Code : %d (%s)\n", code, cw_return_to_string(code));
    fprintf(stderr, "File : %s\n", file);
    fprintf(stderr, "Line : %d\n", line);

    fprintf(stderr, "Message: ");

    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fprintf(stderr, "\n===========================================\n\n");
}
