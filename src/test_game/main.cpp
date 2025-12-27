#include <OpenStg.h>
#include <spdlog/spdlog.h>

int main(int argc, char **args)
{
    SPDLOG_INFO("Program start");
    if(OgInit(0))
    {
        SPDLOG_ERROR("Failed to init og.");
    }
    OG_ELECTROMAGNETIC_DOT_TIMER *pedt = OgCreateElectromagneticDotTimer(10);
    OgRefreshElectromagneticDotTimer(pedt);
    for (size_t sIndex = 0; sIndex < 31; sIndex++)
    {
        SPDLOG_INFO("Ciallo～(∠・ω< )⌒★");
        if (OgElectromagneticDotTimerPullTask(pedt))
        {
            SPDLOG_WARN("发生什么事了？我好像错过了什么？");
        }
        OgElectromagneticDotTimerSkipATimeStamp(pedt);
    }
    OgDestoryElectromagneticDotTimer(pedt);
    OgQuit();
}
