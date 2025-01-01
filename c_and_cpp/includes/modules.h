#include "define.h"
#include <stdint.h>
#ifndef OGAME_MODULES
#define OGAME_MODULES 1
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
ogame_api ogame_error_code init();
#endif // endof OGame/Modules.h