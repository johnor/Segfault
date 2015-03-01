#include "softwareclock.h"

U32 SoftwareClock::GetTimeStampInMicroSecs() const
{
    return currentTimeStamp;
}

void SoftwareClock::SetCurrentTimeStamp(const U32 timeStamp)
{
    currentTimeStamp = timeStamp;
}

void SoftwareClock::IncreaseTimeStamp(const F32 seconds)
{
    const F32 secondsToMicroseconds{1e6f};
    const U32 microseconds{static_cast<U32>(seconds * secondsToMicroseconds)};
    currentTimeStamp += microseconds;
}
