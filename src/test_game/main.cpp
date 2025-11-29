#include <OpenStg.h>
#include <format>
#include <spdlog/spdlog.h>

int main(int argc, char **args)
{
    OgELECTROMAGNETIC_DOT_TIMER *pedt = OgElectromagneticDotTimerCreate(10);
    OgElectromagneticDotTimerRefresh(pedt);
    for (size_t sIndex = 0; sIndex < 31; sIndex++)
    {
        SPDLOG_INFO("Ciallo～(∠・ω< )⌒★");
        if (OgElectromagneticDotTimerPullTask(pedt))
        {
            SPDLOG_WARN("发生什么事了？我好像错过了什么？");
        }
        OgElectromagneticDotTimerSkipATimeStamp(pedt);
    }
    OgElectromagneticDotTimerDestory(pedt);
}