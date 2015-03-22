#include "hardwareclock.h"


const std::chrono::system_clock::time_point HardwareClock::applicationStartTime{HardwareClock::GetCurrentTime()};

U32 HardwareClock::GetTimeStampInMicroSecs() const
{
    auto microSecsSinceStart = std::chrono::duration_cast<std::chrono::microseconds>(GetCurrentTime() - applicationStartTime).count();
    return static_cast<U32>(microSecsSinceStart);
}

TimePoint HardwareClock::GetTime() const
{
    return TimePoint::FromMicroSeconds(GetTimeStampInMicroSecs());
}

void HardwareClock::IncreaseTimeStamp(const F32)
{
}

std::chrono::system_clock::time_point HardwareClock::GetCurrentTime()
{
    return std::chrono::high_resolution_clock::now();
}
