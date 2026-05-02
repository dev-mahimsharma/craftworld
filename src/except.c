#include "except.h"

#include <stdarg.h>
#include <stdio.h>
#include <time.h>

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