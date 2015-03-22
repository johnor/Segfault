#ifndef JOB_H_
#define JOB_H_

#include <asio.hpp>
#include <asio/steady_timer.hpp>
#include <functional>
#include <exception>

class Job
{
public:
    Job(asio::io_service &ioService, std::function<void()> callbackFunction, std::chrono::milliseconds timerDelay);
    ~Job() = default;

private:
    Job(const Job&) = delete;
    const Job& operator=(const Job&) = delete;

    void Timeout();

    asio::steady_timer timer;
    std::chrono::milliseconds timerDelay;

    std::function<void()> callbackFunction;
};

class JobError : public std::runtime_error
{
public:
    explicit JobError(const std::string& what)
        : std::runtime_error{ what } {}
};

#endif