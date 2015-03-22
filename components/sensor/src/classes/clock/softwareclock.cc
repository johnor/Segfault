#include "softwareclock.h"

U32 SoftwareClock::GetTimeStampInMicroSecs() const
{
    return currentTimeStamp.GetTimestamp();
}

TimePoint SoftwareClock::GetTime() const
{
    return currentTimeStamp;
}

void SoftwareClock::IncreaseTimeStamp(const F32 seconds)
{
    currentTimeStamp += TimePoint::FromSeconds(seconds);
}
