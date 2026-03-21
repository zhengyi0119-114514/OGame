#include <OpenStg/OpenStg.h>
#include <fmt/printf.h>
#include <inttypes.h>
#include <spdlog/spdlog.h>

extern "C"
{
    extern int32_t OgLgAdd(uint32_t f, uint32_t s);
}

int main(int argc, char **args)
{
    SPDLOG_INFO("Program start");
    fmt::printf("%" PRId32 "\n", OgLgAdd(1145, 1919));
    if (!OgCrInit())
    {
        SPDLOG_ERROR("Failed to init og.");
    }
    OG_CR_ELECTROMAGNETIC_DOT_TIMER *pedt = OgCrCreateElectromagneticDotTimer(10);
    OgCrRefreshElectromagneticDotTimer(pedt);
    for (size_t sIndex = 0; sIndex < 31; sIndex++)
    {
        SPDLOG_INFO("Ciallo～(∠・ω< )⌒★");
        if (OgCrElectromagneticDotTimerPullTask(pedt))
        {
            SPDLOG_WARN("发生什么事了？我好像错过了什么？");
        }
        OgCrElectromagneticDotTimerSkipATimeStamp(pedt);
    }
    OgCrDestoryElectromagneticDotTimer(pedt);
    
}
