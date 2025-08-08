#include <gtest/gtest.h>
#include "og_math_h.hpp"
namespace math = open_stg::math_h;
TEST(TestCrashDetection,ogmae_lib)
{
    {
        math::circle c{{0,0},1};
        math::point p{1,0};
        ASSERT_TRUE(math::collide(p,c));
    }
}