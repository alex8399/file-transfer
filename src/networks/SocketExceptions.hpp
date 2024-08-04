#ifndef __SOCKET_EXCEPTIONS_HPP__
#define __SOCKET_EXCEPTIONS_HPP__

#include <exception>
#include <string>

#include "../exceptions/Exceptions.hpp"

class BaseSocketException : public BaseException
{
};

class ConnectionFailure : public BaseSocketException
{
public:
    const char *get_message() const noexcept override
    {
        return "Socket connection was not established.";
    }
};

class PacketSendingFailure : public BaseSocketException
{
public:
    const char *get_message() const noexcept override
    {
        return "Packet was not sent in a result of failure.";
    }
};

class PacketRecievingFailure : public BaseSocketException
{
public:
    const char *get_message() const noexcept override
    {
        return "Packet was not recieved in a result of failure.";
    }
};

class PacketExceedMaxSizeException : public BaseSocketException
{
public:
    const char *get_message() const noexcept override
    {
        return "Packet exceeded maximum appropriate size.";
    }
};

class PacketDamagedException : public BaseSocketException
{
public:
    const char *get_message() const noexcept override
    {
        return "Packet was damaged during transmitting.";
    }
};

#endif