#ifndef CLOCK_H_
#define CLOCK_H_

#include "components/common/src/numeric_typedefs.h"

class Clock
{
public:
    virtual ~Clock() {}
    virtual U32 GetTimeStampInMicroSecs() const = 0;
    virtual void IncreaseTimeStamp(const F32 seconds) = 0;
};

#endif
