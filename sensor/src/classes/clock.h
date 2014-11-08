#ifndef TIME_H_
#define TIME_H_

#include <chrono>
#include "headers/numeric_typedefs.h"

class Clock
{
public:
    Clock() = default;
    ~Clock() = default;

    static U32 GetTimeStampInMicroSecs();
private:
    Clock(const Clock&) = delete;
    Clock& operator=(const Clock&) = delete;

    static std::chrono::system_clock::time_point GetCurrentTime();

    static std::chrono::system_clock::time_point applicationStartTime;
};

#endif
