#include <gtest/gtest.h>
#include "og_math_h.hpp"
namespace math = open_stg::math_h;
TEST(TestCrashDetection,ogmae_lib)
{
    {
        math::Circle c{{0,0},1};
        math::Point p{1,0};
        math::Point p2{3,4};
        ASSERT_TRUE(math::CollisionDetection(p,c));
        ASSERT_EQ(math::GetDistanceBetweenTwoPoints(c.center,p2),5);
    }
}