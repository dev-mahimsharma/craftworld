#ifndef CAMERA_H
#define CAMERA_H

#ifdef __CPLUSPLUS
extern "c" {
#endif

#include "raylib.h"

#define CW_CAMERA() (cw_camera_init())

extern Camera3D *cw_camera_init();

#ifdef __CPLUSPLUS
}
#endif

#endif  // !CAMERA_H
