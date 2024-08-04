#ifndef __BASE_PORT_HPP__
#define __BASE_PORT_HPP__

#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <memory>

class BaseSocket
{
public:
    virtual const bool is_open() const = 0;
    virtual const size_t get_packet_size() const = 0;

    virtual void close() = 0;
    virtual ~BaseSocket() = default;
};

class BaseClientSocket : public BaseSocket
{
public:
    virtual void connect() = 0;
    virtual void send(void *buffer, size_t size) = 0;
};

class BaseServerSocket : public BaseSocket
{
public:
    virtual void bind() = 0;
    virtual void listen() = 0;
    virtual void accept() = 0;
    virtual void recv(void *buffer, size_t size) = 0;
};

class BaseSocketFactory
{
public:
    virtual ~BaseSocketFactory() = default;
};

class BaseClientSocketFactory : public BaseSocketFactory
{
public:
    virtual std::shared_ptr<BaseClientSocket> create() = 0;
};

class BaseServerSocketFactory : public BaseSocketFactory
{
public:
    virtual std::shared_ptr<BaseServerSocket> create() = 0;
};

#endif