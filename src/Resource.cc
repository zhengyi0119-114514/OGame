#include "Resource.hh"
#include <SDL_image.h>
#include <SDL_surface.h>
#include <SDL_ttf.h>
namespace OGame::Resources
{
static bool s_HasReadSurfaceFormFile = false;
static GAME_RESOURCE s_Resources;
void GetImageResource(GAME_RESOURCE &resource)
{
    if (!s_HasReadSurfaceFormFile)
    {
        s_Resources.Self = IMG_Load(OGame::Resources::SelfImage.string().c_str());
        s_Resources.CEFFontsCJKFont = TTF_OpenFont(OGame::Resources::CEFFontsCJK.string().c_str(),20);
        s_Resources.CEFFontsCJKMonoFont = TTF_OpenFont(OGame::Resources::CEFFontsCJKMono.string().c_str(),20);
        s_HasReadSurfaceFormFile = true;
    }
    resource = s_Resources;
    return;
}
GAME_RESOURCE GetResources()
{
    GAME_RESOURCE resource;
    GetImageResource(resource);
    return resource;
}
void FreeResource()
{
    if(s_HasReadSurfaceFormFile)
    {
        SDL_FreeSurface(s_Resources.Self);
        TTF_CloseFont(s_Resources.CEFFontsCJKFont);
        TTF_CloseFont(s_Resources.CEFFontsCJKMonoFont);
        s_Resources = {};
        s_HasReadSurfaceFormFile = false;
    }
}
} // namespace OGame::Resources
