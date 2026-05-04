#include "world_init.h"

#include "blocks.h"
#include "cw_returns.h"
#include "raylib.h"

// Store all blocks in a 3D array
int blocks[WORLD_SIZE][WORLD_SIZE][WORLD_SIZE];

// Initialize (fill with stone)
CW_Return InitializeWorld() {
    for (int x = 0; x < WORLD_SIZE; x++) {
        for (int y = 0; y < WORLD_SIZE; y++) {
            for (int z = 0; z < WORLD_SIZE; z++) {
                blocks[x][y][z] = 1;  // 1 = stone
            }
        }
    }

    // add more logic to generate some random glocks in top surface afterward.

    // Make top layer grass
    for (int x = 0; x < WORLD_SIZE; x++) {
        for (int z = 0; z < WORLD_SIZE; z++) {
            blocks[x][WORLD_SIZE - 1][z] = 2;  // 2 = grass
        }
    }
    return CW_OK;
}

CW_Return DrawWorld() {
    for (int x = 0; x < WORLD_SIZE; x++) {
        for (int y = 0; y < WORLD_SIZE; y++) {
            for (int z = 0; z < WORLD_SIZE; z++) {
                if (blocks[x][y][z] != 0) {  // If not air
                    // Draw a cube at this position
                    DrawCube((Vector3){x, y, z},  // Position
                             1, 1, 1,             // Size
                             GRAY                 // Color
                    );
                }
            }
        }
    }

    return CW_OK;
}