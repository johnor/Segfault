#ifndef JOB_H_
#define JOB_H_

#include <asio.hpp>
#include <asio/steady_timer.hpp>
#include <functional>

class Job
{
public:
    Job(asio::io_service &io_service, std::function<void()> callbackFunction, std::chrono::milliseconds timerDelay_);

private:
    Job(const Job&) = delete;
    const Job& operator=(const Job&) = delete;

    void Timeout();

    asio::steady_timer timer;
    std::chrono::milliseconds timerDelay;

    std::function<void()> callbackFunction;
};

#endif