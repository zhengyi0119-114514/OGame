#ifndef OGAME_STGLIB_MV_H
#define OGAME_STGLIB_MV_H 1
#include "og_module.hpp"
#include "og_view.hpp"
#include <concepts>

namespace open_stg::module_view_h
{
template <typename TSourceType>
    requires std::derived_from<TSourceType, mod_h::IGameObject>
struct IGameObjectViewObjectMapper
{
    virtual ~IGameObjectViewObjectMapper() noexcept = default;
    virtual view_h::SharedPtrIImageOutput GetImageOutput(const TSourceType &) = 0;
    virtual view_h::SharedPtrIAudioOutput GetAudioOutput(const TSourceType &) = 0;
};
} // namespace open_stg::module_view_h
#endif