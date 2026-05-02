#ifndef RETURNS_H
#define RETURNS_H

#ifdef __CPLUSPLUS
extern "c" {
#endif

/*
    Common return/status codes for Craftworld.

    Use these instead of random numbers like:
        return 0;
        return -1;

    Example:
        if (!load_texture()) {
            return CW_ERROR_ASSET_LOAD_FAILED;
        }
*/

typedef enum CW_Return {
    CW_OK = 0,

    /* General errors */
    CW_ERROR = -1,
    CW_ERROR_UNKNOWN = -2,
    CW_ERROR_INVALID_ARGUMENT = -3,
    CW_ERROR_NULL_POINTER = -4,
    CW_ERROR_OUT_OF_MEMORY = -5,

    /* File / asset errors */
    CW_ERROR_FILE_NOT_FOUND = -100,
    CW_ERROR_FILE_READ_FAILED = -101,
    CW_ERROR_FILE_WRITE_FAILED = -102,
    CW_ERROR_ASSET_LOAD_FAILED = -103,
    CW_ERROR_ASSET_UNLOAD_FAILED = -104,

    /* Window / raylib errors */
    CW_ERROR_WINDOW_INIT_FAILED = -200,
    CW_ERROR_WINDOW_NOT_READY = -201,
    CW_ERROR_RENDER_FAILED = -202,

    /* Game system errors */
    CW_ERROR_WORLD_INIT_FAILED = -300,
    CW_ERROR_PLAYER_INIT_FAILED = -301,
    CW_ERROR_CAMERA_INIT_FAILED = -302,
    CW_ERROR_INPUT_INIT_FAILED = -303,

    /* Runtime states */
    CW_QUIT = 100,
    CW_RESTART = 101,
    CW_PAUSE = 102,
    CW_CONTINUE = 103

} CW_Return;

/*
    Optional helper macro.
    Example:
        if (result != CW_OK) {
            return result;
        }
*/
#define CW_FAILED(result) ((result) < 0)
#define CW_SUCCESS(result) ((result) >= 0)

#ifdef __CPLUSPLUS
}
#endif

#endif /* RETURNS_H */