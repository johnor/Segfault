#include "hardwareclock.h"


const std::chrono::system_clock::time_point HardwareClock::applicationStartTime{HardwareClock::GetCurrentTime()};

TimePoint HardwareClock::GetTime() const
{
    return TimePoint::FromMicroSeconds(GetTimeInMicroSecs());
}

void HardwareClock::IncreaseTime(const F32)
{
}

std::chrono::system_clock::time_point HardwareClock::GetCurrentTime()
{
    return std::chrono::high_resolution_clock::now();
}

U32 HardwareClock::GetTimeInMicroSecs() const
{
    auto microSecsSinceStart = std::chrono::duration_cast<std::chrono::microseconds>(GetCurrentTime() - applicationStartTime).count();
    return static_cast<U32>(microSecsSinceStart);
}
