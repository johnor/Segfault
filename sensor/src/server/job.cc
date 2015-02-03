#include "job.h"
#include <chrono>
#include <iostream>

Job::Job(asio::io_service &io_service, std::function<void()> callbackFunction, std::chrono::milliseconds timerDelay_)
: callbackFunction{ callbackFunction }, timer{ io_service }, timerDelay{ timerDelay_ }
{
    Timeout();
}

void Job::Timeout()
{
    timer.expires_from_now(timerDelay);
    timer.async_wait([this](std::error_code ec)
    {
        if (!ec)
        {
            std::cout << "Timeout" << std::endl;
            callbackFunction();
        }

        Timeout();
    });
}

