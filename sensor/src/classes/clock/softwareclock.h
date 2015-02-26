#ifndef SOFTWARECLOCK_H_
#define SOFTWARECLOCK_H_

#include "headers/numeric_typedefs.h"
#include "interfaces/clock.h"

class SoftwareClock : public Clock
{
public:
    SoftwareClock() = default;
    virtual ~SoftwareClock() {};

    virtual U32 GetTimeStampInMicroSecs() const override;
    virtual void IncreaseTimeStamp(const F32 seconds) override;

    void SetCurrentTimeStamp(const U32 currentTimeStamp_);
private:
    SoftwareClock(const SoftwareClock&) = delete;
    SoftwareClock& operator=(const SoftwareClock&) = delete;
    
    U32 currentTimeStamp{ 0 };
};

#endif
