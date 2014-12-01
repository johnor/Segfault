#include "softwareclock.h"

U32 SoftwareClock::GetTimeStampInMicroSecs()
{
    return currentTimeStamp;
}

void SoftwareClock::SetCurrentTimeStamp(const U32 currentTimeStamp_)
{
    currentTimeStamp = currentTimeStamp_;
}

void SoftwareClock::IncreaseTimeStamp(const F32 seconds)
{
    currentTimeStamp += static_cast<U32>(seconds * 1e6);
}

