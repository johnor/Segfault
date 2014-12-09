#ifndef HARDWARECLOCK_H_
#define HARDWARECLOCK_H_

#include "headers/numeric_typedefs.h"
#include "interfaces/clock.h"
#include <chrono>

class HardwareClock : public Clock
{
public:
    HardwareClock() = default;
    virtual ~HardwareClock() {};

    virtual U32 GetTimeStampInMicroSecs() const override;
private:
    HardwareClock(const HardwareClock&) = delete;
    HardwareClock& operator=(const HardwareClock&) = delete;

    static std::chrono::system_clock::time_point GetCurrentTime();
    static const std::chrono::system_clock::time_point applicationStartTime;
};

#endif
