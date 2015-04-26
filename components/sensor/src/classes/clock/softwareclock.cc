#include "softwareclock.h"

TimePoint SoftwareClock::GetTime() const
{
    return currentTime;
}

void SoftwareClock::IncreaseTime(const F32 seconds)
{
    currentTime += TimePoint::FromSeconds(seconds);
}
