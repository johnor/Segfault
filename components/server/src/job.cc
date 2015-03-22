#include "job.h"

#include <chrono>
#include <sstream>

Job::Job(asio::io_service &ioService, std::function<void()> callbackFunction, std::chrono::milliseconds timerDelay)
: timer{ ioService }, timerDelay{ timerDelay }, callbackFunction{ callbackFunction }
{
    Timeout();
}

void Job::Timeout()
{
    timer.expires_from_now(timerDelay);
    callbackFunction();

    timer.async_wait(
        [this](const std::error_code &errorCode)
    {
        if (!errorCode)
        {
            Timeout();
        }
        else
        {
            std::ostringstream msg;
            msg << errorCode;
            throw JobError(msg.str());
        }
    });
}

