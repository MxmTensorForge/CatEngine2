#define _CRT_SECURE_NO_WARNINGS

#include "Logger.h"

#include <ctime>
#include <iostream>

std::string Logger::logTypeToStr(LogType type) const {
	switch (type) {
	case LogType::Message: return "[MESSAGE]";
	case LogType::Warning: return "[WARNING]";
	case LogType::Error: return "[ERROR]";
	case LogType::Fatal: return "[FATAL]";
	}
	return "[UNKOWN]";
}
std::string Logger::getTimestep() const {
	time_t t = std::time(nullptr);
	std::string str(std::ctime(&t));
	str.pop_back(); //remove \n

	return str;
}

Logger& Logger::getInstance() {
	static Logger logger;
	return logger;
}

void Logger::setLogFile(const std::string& name) {
	_file.open(name, std::ios::ate | std::ios::out);
}
void Logger::log(LogType type, const std::string& info) {
	std::string out = "[" + getTimestep() + "]" + logTypeToStr(type) + ": " + info;

	std::cout << out << std::endl;

	if (_file.is_open()) {
		_file << out << std::endl;
	}
	if (type == LogType::Fatal) {
		std::cerr << "Fatal error, shutting down..." << std::endl;
		std::terminate();
	}
}
