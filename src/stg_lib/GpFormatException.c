#include "CloseStgGraphics.h"
#include <SDL3/SDL.h>
#include <safec.h>
void OG_API OgGpFormatErrorMessage(OG_ERROR_CODE_T code, char *pszBuffer, uint64_t uLengthOfBuffer)
{
    switch (code)
    {
    case OPEN_STG_ERROR_MESSAGE_SDL3_INIT_FAILED: {
        snprintf(pszBuffer, uLengthOfBuffer, "SDL3 init failed:%s", SDL_GetError());
        break;
    }
    }
}