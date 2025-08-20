#include "og_stg_h.hpp"
#include <utility>
namespace open_stg::stg
{
math_h::Point &HitBoxBase::GetCenter() noexcept
{
    return const_cast<math_h::Point &>(std::as_const(*this).GetCenter());
}
} // namespace open_stg::stg