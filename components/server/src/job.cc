#include "job.h"

#include <chrono>
#include <iostream>

Job::Job(asio::io_service &io_service, std::function<void()> callbackFunction, std::chrono::milliseconds timerDelay_)
: timer{ io_service }, timerDelay{ timerDelay_ }, callbackFunction{ callbackFunction }
{
    Timeout();
}

void Job::Timeout()
{
    timer.expires_from_now(timerDelay);
    callbackFunction();

    timer.async_wait([this](std::error_code ec)
    {
        Timeout();
    });
}

