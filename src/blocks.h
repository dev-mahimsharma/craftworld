#ifndef BLOCKS_H
#define BLOCKS_H

#ifdef __CPLUSPLUS
extern "c" {
#endif

typedef enum {

    BLOCK_AIR = 0,  // Empty space
    BLOCK_STONE = 1,
    BLOCK_DIRT = 2,
    BLOCK_GRASS = 3,
    BLOCK_WOOD = 4,
    BLOCK_LEAVES = 5,
    BLOCK_WATER = 6,
    BLOCK_SAND = 7,
    BLOCK_GRAVEL = 8,
    BLOCK_COAL_ORE = 9,
    BLOCK_IRON_ORE = 10
    // add more later

} blocks_t;

#ifdef __CPLUSPLUS
}
#endif

#endif