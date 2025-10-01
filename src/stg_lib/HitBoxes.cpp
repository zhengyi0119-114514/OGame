#include "og_stg_h.hpp"
#include <utility>
namespace OpenGame::STG
{
Math::Point &HitBox::GetCenter() noexcept
{
    return const_cast<Math::Point &>(std::as_const(*this).GetCenter());
}
} // namespace OpenGame::stg