/**
 * @file StgScenePosix.cpp
 * @author iCeThOrn
 * @brief
 * @version Ciallo～(∠・ω< )⌒★
 * @date 2025-08-07
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "og_module.hpp"
#include <math.h>
#include <time.h>
namespace open_stg::mod_h
{
STGScene::stg_scene() : scene()
{
    m_sSize = {500, 900};
    m_uOperationsPerSecond = STGScene::OperationsPerSecond;
}
#if defined POSIX && !defined DEFINED_SLEEP_FUNCTION
#define DEFINED_SLEEP_FUNCTION
static struct timespec s_lastRun{};
void Scene::wait_to_next_operation(IRegister* reg)
{
    struct timespec now;
    struct timespec time_to_sleep_s{}; //需要等待的时间
    long double time_passed{}; //距离上次调用的时间
    clock_gettime(CLOCK_MONOTONIC, &now); 
    time_passed = (now.tv_sec - s_lastRun.tv_sec) + (now.tv_nsec - s_lastRun.tv_nsec) * 0.000'000'001L; // second
    s_lastRun = now;
    long double time_need_to_wait = 1.0 / m_uOperationsPerSecond;
    long double time_to_wait = time_need_to_wait - time_passed;
    if (time_to_wait >= 0)
    {
        time_to_sleep_s.tv_nsec = (time_t)time_need_to_wait * 1e9;
        clock_nanosleep(CLOCK_MONOTONIC, 0, &time_to_sleep_s, nullptr);
    }
    s_lastRun = now;
    if(!reg)
    {
        reg->registered();
    }
    static_assert(0.000'000'001 == 1e-9);
    static_assert(1'000'000'000 == 1e9);
}
#endif
#if defined WIN32 && !defined DEFINED_SLEEP_FUNCTION
#define DEFINED_SLEEP_FUNCTION
#endif

} // namespace open_stg::mod_h