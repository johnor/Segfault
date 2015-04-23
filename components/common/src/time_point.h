#ifndef TIME_H_A
#define TIME_H_A

#include "components/common/src/numeric_typedefs.h"

class TimePoint
{
public:
    static TimePoint FromSeconds(const F32 seconds);
    static TimePoint FromMicroSeconds(const U32 microSeconds);
    static TimePoint FromTimeStamp(const U32 timeStamp);

    TimePoint(const TimePoint &time);
    ~TimePoint() = default;

    U32 GetTimestamp() const;
    F32 GetSeconds() const;

    TimePoint& operator+=(const TimePoint& rhs);
    TimePoint& operator-=(const TimePoint& rhs);

    TimePoint& operator=(TimePoint other);

private:
    explicit TimePoint(const U32 microSecs);

    void swap(TimePoint &first, TimePoint &second);

    U32 timeStampInMicroSeconds{ 0u };

    static const U32 secondsToMicroSeconds{ 1000000u };
    static const U32 timeStampToMicroSeconds{ 1u };
};

inline TimePoint operator+(TimePoint lhs, const TimePoint& rhs)
{
    lhs += rhs;
    return lhs;
}

inline TimePoint operator-(TimePoint lhs, const TimePoint& rhs)
{
    lhs -= rhs;
    return lhs;
}

inline bool operator==(const TimePoint& lhs, const TimePoint& rhs)
{
    return lhs.GetTimestamp() == rhs.GetTimestamp();
}
inline bool operator!=(const TimePoint& lhs, const TimePoint& rhs)
{
    return !operator==(lhs, rhs);
}
inline bool operator<(const TimePoint& lhs, const TimePoint& rhs)
{
    return lhs.GetTimestamp() < rhs.GetTimestamp();
}
inline bool operator>(const TimePoint& lhs, const TimePoint& rhs)
{
    return  operator<(rhs, lhs);
}
inline bool operator<=(const TimePoint& lhs, const TimePoint& rhs)
{
    return !operator>(lhs, rhs);
}
inline bool operator>=(const TimePoint& lhs, const TimePoint& rhs)
{
    return !operator<(lhs, rhs);
}

#endif
