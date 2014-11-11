#include "logger.h"
#include <iostream>

/* Logger implementation */
void Logger::Log(const std::string &message)
{
	auto logger = Logger::GetInstance();

	logger->fs << message << std::endl;
	std::cout << message << std::endl;
}

void Logger::Log(const LogLevel level, const std::string &message)
{
	std::stringstream fullMessage;
	fullMessage << "[" << getStringFromLogLevel(level) << "] ";
	fullMessage << message;

	Logger::Log(fullMessage.str());
}

LogStream Logger::Log()
{
	auto logger = Logger::GetInstance();
	return LogStream(*logger, LogLevel::Info);
}

LogStream Logger::Log(const LogLevel level)
{
	auto logger = Logger::GetInstance();
	return LogStream(*logger, level);
}

/* Private function implementations */

Logger::Logger()
{
	fs.open(filename);
	fs << "Logger created!" << std::endl;
}

std::shared_ptr<Logger>& Logger::GetInstance()
{
	static std::shared_ptr<Logger> instance = nullptr;

	if (instance == nullptr)
	{
		instance = std::shared_ptr<Logger>{new Logger};
	}
	return instance;
}

std::string Logger::getStringFromLogLevel(const LogLevel level)
{
	std::string res;

	switch (level)
	{
	case LogLevel::Debug:
		res = "Debug";
		break;
	case LogLevel::Error:
		res = "Error";
		break;
	case LogLevel::Info:
		res = "Info";
		break;
	case LogLevel::Warning:
		res = "Warning";
		break;
	default:
		return "";
	}
	return res;
}


LogStream::LogStream(Logger& logger_, LogLevel level_) :
std::ostringstream{}, logger{ logger_ }, level{ level_ }
{
}

LogStream::LogStream(const LogStream& ls) :
std::basic_ios<char>{}, std::ostringstream{}, logger{ ls.logger }, level{ ls.level }
{
}

LogStream::~LogStream()
{
	logger.Log(level, str());
}
