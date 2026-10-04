#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

enum class LogType
{
	Message,
	Warning,
	Error,
	Fatal
};

class Logger final
{
private:
	std::ofstream _file;

	std::string logTypeToStr(LogType type) const;
	std::string getTimestep() const;

	Logger() = default;
	~Logger() = default;
public:

	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
	Logger(Logger&&) = delete;
	Logger& operator=(Logger&&) = delete;

	static Logger& getInstance();

	void setLogFile(const std::string& name);
	void log(LogType type, const std::string& info);
};

#endif // !LOGGER_H
