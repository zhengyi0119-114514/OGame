#include <gtest/gtest.h>
#include "og.hpp"
int main(int argc, char** args)
{
    bool bOk{false};
    ::testing::InitGoogleTest(&argc,args);
    ::open_stg::InitOpenGame();
    return RUN_ALL_TESTS();
}