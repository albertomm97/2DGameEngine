#define _CRT_SECURE_NO_WARNINGS 1

#include "Logger.h"
#include <chrono>
#include <iostream>
#include <ctime>


std::vector<LogEntry> Logger::messages;

void Logger::Log(const std::string& message)
{
	LogEntry logEntry;
	logEntry.type = LOG_INFO;
	logEntry.message = "LOG (" + CurrentDateTimeToString() + "): " + message;
	std::cout << "\x1B[32m" << logEntry.message << "\033[0m" << "\n";
	messages.push_back(logEntry);
}

void Logger::Warn(const std::string& message)
{
	LogEntry logEntry;
	logEntry.type = LOG_WARNING;
	logEntry.message = "WRN (" + CurrentDateTimeToString() + "): " + message;
	std::cout << "\x1B[33m" << logEntry.message << "\033[0m" << "\n";
	messages.push_back(logEntry);
}

void Logger::Error(const std::string& message)
{
	LogEntry logEntry;
	logEntry.type = LOG_ERROR;
	logEntry.message = "ERR (" + CurrentDateTimeToString() + "): " + message;
	std::cout << "\x1B[91m" << logEntry.message << "\033[0m" << "\n";
	messages.push_back(logEntry);
}

std::string Logger::CurrentDateTimeToString()
{
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string output(30, '\0');
	std::strftime(&output[0], output.size(), "%d-%b-%Y %H:%M:%S", std::localtime(&now));
	return output;
}