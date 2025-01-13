#include <stdint.h>
typedef struct
{
    int32_t x;
    int32_t y;
} OGame_Point;
typedef struct
{
    OGame_Point pCenter;
    int32_t iReadius;
} OGame_Circle;
typedef struct
{
    int32_t iWeight;
    int32_t iHeight;
} OGame_Rectangle;