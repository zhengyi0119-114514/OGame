#include "OpenStg/CloseStgGraphics.h"
#include <SDL3/SDL.h>
#include <stdio.h>
void OG_API OgGpFormatErrorMessage(OG_ERROR_CODE_T code, char *pszBuffer, uint64_t uLengthOfBuffer)
{
    switch (code)
    {
    case OPEN_STG_ERROR_CODE_GRAPHICS_INIT_FAILED: {
        snprintf(pszBuffer, uLengthOfBuffer, "SDL3 init failed:%s", SDL_GetError());
        break;
    }
    }
}
