#include <chrono>

#include "hardwareclock.h"
#include "classes/logger.h"

std::chrono::system_clock::time_point HardwareClock::applicationStartTime{ HardwareClock::GetCurrentTime() };

U32 HardwareClock::GetTimeStampInMicroSecs() const
{
    auto microSecsSinceStart = std::chrono::duration_cast<std::chrono::microseconds>(GetCurrentTime() - applicationStartTime).count();
    Logger::Log(LogLevel::Debug) << "Get time microseconds: " << microSecsSinceStart;

    return static_cast<U32>(microSecsSinceStart);
}

std::chrono::system_clock::time_point HardwareClock::GetCurrentTime()
{
    return std::chrono::high_resolution_clock::now();
}
