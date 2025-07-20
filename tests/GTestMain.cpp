#include <gtest/gtest.h>
#include "open_game.hpp"
int main(int argc, char** args)
{
    bool bOk{false};
    ::testing::InitGoogleTest(&argc,args);
    ::open_stg::InitOG_h(bOk);
    return RUN_ALL_TESTS();
}