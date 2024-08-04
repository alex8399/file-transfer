#ifndef __CONSOLE_LOGGER_HPP__
#define __CONSOLE_LOGGER_HPP__

#include <iostream>
#include <string>

#include "BaseLogger.hpp"

#define LOGGER_LINE "---------------------------------------------------------------------------"

class ConsoleLogger : public BaseLogger
{
private:
    std::ostream &stream;

    void write(const std::string &message);

public:
    ConsoleLogger(std::ostream &stream);

    void log(const std::string &message) override;
    void draw_line() override;
};

#endif