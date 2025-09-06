#include <gtest/gtest.h>
#include "og_math_h.hpp"
namespace math = OpenGame::Math;
TEST(TestCrashDetection,ogmae_lib)
{
    {
        math::Circle c{{0,0},1};
        math::Point p{1,0};
        math::Point p2{3,4};
        ASSERT_EQ(math::GetDistanceBetweenTwoPoints(c.center,p2),5);
    }
}