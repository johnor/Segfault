#ifndef CLOCK_H_
#define CLOCK_H_

#include "headers/numeric_typedefs.h"

class Clock
{
public:
    virtual ~Clock() {}
    virtual U32 GetTimeStampInMicroSecs() const = 0;
};

#endif
