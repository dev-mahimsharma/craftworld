#ifndef WORLD_INIT_H
#define WORLD_INIT_H

#ifdef __CPLUSPLUS
extern "c" {
#endif

#include "cw_returns.h"

#define WORLD_SIZE 16

#define CW_WORLD_INIT() InitializeWorld()
#define CW_WORLD_DRAW() DrawWorld()

CW_Return InitializeWorld();

CW_Return DrawWorld();

#ifdef __CPLUSPLUS
}
#endif  // DEBUG

#endif  // !WORLD_INIT_H