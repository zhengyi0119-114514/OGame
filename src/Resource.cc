#include "Resource.hh"
#include <SDL_image.h>
namespace OGame::Resources
{
static bool s_HasReadSurfaceFormFile = false;
static IMAGE_RESOURCE s_Images;
void GetImageResource(IMAGE_RESOURCE &resource)
{
    if (!s_HasReadSurfaceFormFile)
    {
        s_Images.Self = IMG_Load(OGame::Resources::SelfImage.string().c_str());
        s_HasReadSurfaceFormFile = true;
    }
    resource = s_Images;
    return;
}
} // namespace OGame::Resources
