#include <OpenStg.h>
#include <spdlog/spdlog.h>

int main(int argc, char **args)
{
    SPDLOG_INFO("Program start");
    if(!OgCrInit())
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
