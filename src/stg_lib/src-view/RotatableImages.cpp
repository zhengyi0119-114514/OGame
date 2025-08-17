#include "og.hpp"
namespace open_stg::view_h
{
RotatableImage::RotatableImage(sdl3_h::SharedPtrSurface spSurface, math_h::Point location, double angleOfRotation)
    : m_spLocation(location), m_spSourceSurface(spSurface), m_spTexture(updateTexture())
{
}
} // namespace open_stg::view_h