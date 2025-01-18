#define OGAME_EXPORT
#include "modules/math.hpp"
#include <math.h>

namespace ogame::math
{
Line::Line(const Point &form, const Point to) : m_form{form}, m_to{to}
{
}
const Point &Line::Form() const noexcept
{
    return ref_this.m_form;
}
const Point &Line::To() const noexcept
{
    return ref_this.m_to;
}
} // namespace ogame::math