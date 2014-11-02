
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
	LogStream(Logger& oLogger, LogLevel level);
	LogStream(const LogStream& ls);
	~LogStream();

private:
	Logger &logger;
	LogLevel level;
};

class Logger
{
public:
	~Logger() = default;

	static void Log(const std::string &message);
	static void Log(const LogLevel level, const std::string &message);

	static LogStream Log();
	static LogStream Log(LogLevel level);

private:
	Logger();
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	static std::shared_ptr<Logger>& GetInstance();
	static std::string getStringFromLogLevel(const LogLevel level);

	std::string filename = "log.txt";
	std::ofstream fs;
};


#endif
