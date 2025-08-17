#include <gtest/gtest.h>
#include "og.hpp"
int main(int argc, char** args)
{
    ::open_stg::InitOpenGame();
    ::testing::InitGoogleTest(&argc,args);
    return RUN_ALL_TESTS();
}