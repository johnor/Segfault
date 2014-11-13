
#ifndef LOG_H_
#define LOG_H_

#include <fstream>
#include <sstream>
#include <memory>
#include <string>

enum class LogLevel
{
	Debug = 0,
	Info,
	Warning,
	Error
};

class Logger;

class LogStream : public std::ostringstream
{
public:
	LogStream(Logger& logger, const LogLevel level);
	LogStream(const LogStream& ls);
	~LogStream();

private:
	Logger &logger;
	LogLevel level;
};

class Logger
{
public:
    friend class LogStream;
	~Logger() = default;

    Logger(const std::string &filename);
    LogStream operator()();
    LogStream operator()(const LogLevel level);

    static void SetRootLoggerFilename(const std::string &filename);
	static LogStream Log();
	static LogStream Log(const LogLevel level);
private:
	Logger();
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

    void WriteMessageToFile(const std::string &message);
    void FormatMessageAndLog(const LogLevel level, const std::string &message);

	static std::shared_ptr<Logger>& GetRootInstance();
    static std::string GetStringFromLogLevel(const LogLevel level);

    static std::string rootLoggerFilename;
	std::ofstream fileStream;
};


#endif
