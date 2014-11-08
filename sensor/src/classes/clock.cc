#include <chrono>

#include "clock.h"
#include "classes/logger.h"

std::chrono::system_clock::time_point Clock::applicationStartTime{ Clock::GetCurrentTime() };

U32 Clock::GetTimeStampInMicroSecs()
{
    auto microSecsSinceStart = std::chrono::duration_cast<std::chrono::microseconds>(GetCurrentTime() - applicationStartTime).count();
    Logger::Log(LogLevel::Debug) << "Get time microseconds: " << microSecsSinceStart;

    return static_cast<U32>(microSecsSinceStart);
}


std::chrono::system_clock::time_point Clock::GetCurrentTime()
{
    return std::chrono::high_resolution_clock::now();
}
