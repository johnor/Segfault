#ifndef CLOCK_H_
#define CLOCK_H_

#include "components/common/src/numeric_typedefs.h"
#include "components/common/src/time_point.h"

class Clock
{
public:
    virtual ~Clock() {}
    virtual TimePoint GetTime() const = 0;
    virtual void IncreaseTime(const F32 seconds) = 0;
};

#endif
