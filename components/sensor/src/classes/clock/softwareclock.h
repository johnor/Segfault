#ifndef SOFTWARE_CLOCK_H_
#define SOFTWARE_CLOCK_H_

#include "common/src/numeric_typedefs.h"
#include "common/src/time_point.h"
#include "interfaces/clock.h"

class SoftwareClock : public Clock
{
public:
    SoftwareClock() = default;
    virtual ~SoftwareClock() {};

    virtual TimePoint GetTime() const override;
    virtual void IncreaseTime(const F32 seconds) override;
private:
    SoftwareClock(const SoftwareClock&) = delete;
    SoftwareClock& operator=(const SoftwareClock&) = delete;

    TimePoint currentTime{TimePoint::FromSeconds(0.f)};
};

#endif
