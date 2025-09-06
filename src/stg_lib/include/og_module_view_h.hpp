#ifndef OGAME_STGLIB_MV_H
#define OGAME_STGLIB_MV_H 1
#include "og_macro.h"
#include "og_module.hpp"
#include "og_view.hpp"

namespace OpenGame::ModuleView
{
template <typename TSourceType> OG_INTERFACE IGameObjectViewObjectMapper
{
    virtual ~IGameObjectViewObjectMapper() noexcept = default;
    virtual View::SharedPtrIImageOutput GetImageOutput(const TSourceType &s, SDL_Renderer *pRenderer) = 0;
    virtual View::SharedPtrIAudioOutput GetAudioOutput(const TSourceType &s, SDL_Renderer *pRenderer) = 0;
};
class MotionController
{
    
};
} // namespace OpenGame::ModuleView
#endif