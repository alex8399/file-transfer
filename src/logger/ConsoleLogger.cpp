#include "ConsoleLogger.hpp"

ConsoleLogger::ConsoleLogger(std::ostream &stream) : stream(stream) {}

void ConsoleLogger::write(const std::string &message)
{
    this->stream << message << std::endl;
}

void ConsoleLogger::log(const std::string &message)
{
    this->write(message);
}

void ConsoleLogger::draw_line()
{
    this->write(std::string(LOGGER_LINE));
}