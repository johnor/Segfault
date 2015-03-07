#ifndef HARDWARE_CLOCK_H_
#define HARDWARE_CLOCK_H_

#include <chrono>
#include "../../headers/numeric_typedefs.h"
#include "../../interfaces/clock.h"

class HardwareClock : public Clock
{
public:
    HardwareClock() = default;
    virtual ~HardwareClock() {};

    virtual U32 GetTimeStampInMicroSecs() const override;
    virtual void IncreaseTimeStamp(const F32 seconds) override;
private:
    HardwareClock(const HardwareClock&) = delete;
    HardwareClock& operator=(const HardwareClock&) = delete;

    static std::chrono::system_clock::time_point GetCurrentTime();
    static const std::chrono::system_clock::time_point applicationStartTime;
};

#endif
