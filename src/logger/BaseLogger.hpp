#ifndef __BASE_LOGGER_HPP__
#define __BASE_LOGGER_HPP__

#include <iostream>

class BaseLogger
{
public:
    virtual void log(const std::string &message) = 0;
    virtual void draw_line() = 0;

    virtual ~BaseLogger() = default;
};

#endif