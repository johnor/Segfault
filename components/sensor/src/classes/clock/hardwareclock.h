#ifndef HARDWARE_CLOCK_H_
#define HARDWARE_CLOCK_H_

#include "components/common/src/numeric_typedefs.h"
#include "components/common/src/time_point.h"
#include "interfaces/clock.h"
#include <chrono>

class HardwareClock : public Clock
{
public:
    HardwareClock() = default;
    virtual ~HardwareClock() {};

    virtual TimePoint GetTime() const override;
    virtual void IncreaseTime(const F32 seconds) override;
private:
    HardwareClock(const HardwareClock&) = delete;
    HardwareClock& operator=(const HardwareClock&) = delete;

    U32 GetTimeInMicroSecs() const;

    static std::chrono::system_clock::time_point GetCurrentTime();

    static const std::chrono::system_clock::time_point applicationStartTime;
};

#endif
