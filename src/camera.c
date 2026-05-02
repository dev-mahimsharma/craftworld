#include "camera.h"

#include "cw_returns.h"
#include "except.h"
#include "raylib.h"

#include <stdlib.h>

Camera3D *cw_camera_init() {

    Camera3D *cw_camera = MemAlloc(sizeof(Camera3D));
    if (cw_camera == NULL) {
        CW_THROW(CW_ERROR_CAMERA_INIT_FAILED, "failed to initialize memory for camera.\n");
    }

    cw_camera->position = (Vector3){0.0f, 2.0f, 6.0f};  // where camera is
    cw_camera->target = (Vector3){0.0f, 1.0f, 0.0f};    // where camera looks
    cw_camera->up = (Vector3){0.0f, 1.0f, 0.0f};        // upward direction
    cw_camera->fovy = 60.0f;                            // field of view
    cw_camera->projection = CAMERA_PERSPECTIVE;

    return cw_camera;
}
