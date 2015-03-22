#include "time_point.h"
#include <chrono>
#include <algorithm>

TimePoint::TimePoint(const U32 microSecs)
: timeStampInMicroSeconds{microSecs}
{
}

TimePoint::TimePoint(const TimePoint& time)
: timeStampInMicroSeconds{time.timeStampInMicroSeconds}
{
}

TimePoint TimePoint::FromSeconds(const F32 seconds)
{
    const U32 microSeconds = static_cast<U32>(seconds * secondsToMicroSeconds);
    return TimePoint(microSeconds);
}


TimePoint TimePoint::FromMicroSeconds(const U32 microSeconds)
{
    return TimePoint(microSeconds);
}


TimePoint TimePoint::FromTimeStamp(const U32 timeStamp)
{
    return TimePoint(timeStamp * timeStampToMicroSeconds);
}

U32 TimePoint::GetTimestamp() const
{
    return timeStampInMicroSeconds;
}

F32 TimePoint::GetSeconds() const
{
    return static_cast<F32>(timeStampInMicroSeconds) / secondsToMicroSeconds;
}

TimePoint& TimePoint::operator+=(const TimePoint& rhs)
{
    timeStampInMicroSeconds += rhs.timeStampInMicroSeconds;
    return *this;
}

TimePoint& TimePoint::operator-=(const TimePoint& rhs)
{
    timeStampInMicroSeconds -= rhs.timeStampInMicroSeconds;
    return *this;
}

TimePoint& TimePoint::operator=(TimePoint other)
{
    swap(*this, other);
    return *this;
}

void TimePoint::swap(TimePoint &first, TimePoint &second)
{
    std::swap(first.timeStampInMicroSeconds, second.timeStampInMicroSeconds);
}
