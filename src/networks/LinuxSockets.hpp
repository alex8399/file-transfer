#ifndef __LINUX_TCP_SOCKET_HPP__
#define __LINUX_TCP_SOCKET_HPP__

#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <memory>
#include <unistd.h>

#include "SocketInterfaces.hpp"
#include "SocketExceptions.hpp"

class LinuxSocket
{

protected:
    bool open = false;
    int descriptor;

public:
    static const size_t PACKET_SIZE = 1000;
    static const int SYS_SOCKET_ERROR_VALUE = -1;

    const bool is_open() const
    {
        return this->open;
    }
};

class LinuxClientSocket : public BaseClientSocket, public LinuxSocket
{
private:
    sockaddr_in server_address;

public:
    LinuxClientSocket(in_addr_t &ip_address, int port);

    void connect() override;
    void send(void *buffer, size_t size) override;

    const size_t get_packet_size() const override;
    const bool is_open() const override;

    void close() override;
};

class LinuxServerSocket : public BaseServerSocket, public LinuxSocket
{
private:
    sockaddr_in server_address;
    int client_descriptor;

public:
    LinuxServerSocket(in_addr_t &ip_address, int port);
    LinuxServerSocket(int port);

    void bind() override;
    void listen() override;
    void accept() override;
    void recv(void *buffer, size_t size) override;

    const size_t get_packet_size() const override;
    const bool is_open() const override;

    void close() override;
};

class LinuxClientSocketFactory : public BaseClientSocketFactory
{
private:
    std::string ip_address;
    int port;

public:
    LinuxClientSocketFactory(std::string &str_ip_address, int port);
    std::shared_ptr<BaseClientSocket> create() override;
};

class LinuxServerSocketFactory : public BaseServerSocketFactory
{
private:
    int port;

public:
    LinuxServerSocketFactory(int port);
    std::shared_ptr<BaseServerSocket> create() override;
};

#endif