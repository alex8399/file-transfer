#include "LinuxSockets.hpp"

LinuxClientSocket::LinuxClientSocket(in_addr_t &ip_address, int port)
{
    this->server_address.sin_family = AF_INET;
    this->server_address.sin_port = ::htons(port);
    this->server_address.sin_addr.s_addr = ip_address;

    int socket_descriptor = ::socket(AF_INET, SOCK_STREAM, 0);

    if (socket_descriptor == this->SYS_SOCKET_ERROR_VALUE)
    {
        throw ConnectionFailure();
    }

    this->descriptor = socket_descriptor;
}

void LinuxClientSocket::connect()
{
    int return_code = ::connect(
        this->descriptor, (struct sockaddr *)&(this->server_address),
        sizeof(this->server_address));

    if (return_code == this->SYS_SOCKET_ERROR_VALUE)
    {
        throw ConnectionFailure();
    }

    this->open = true;
}

void LinuxClientSocket::send(void *buffer, size_t size)
{
    if (size > this->get_packet_size())
    {
        throw PacketExceedMaxSizeException();
    }

    int sent_bytes = ::send(this->descriptor, buffer, size, 0);

    if (sent_bytes == this->SYS_SOCKET_ERROR_VALUE)
    {
        throw PacketSendingFailure();
    }
    else if (sent_bytes != size)
    {
        throw PacketDamagedException();
    }
}

const size_t LinuxClientSocket::get_packet_size() const
{
    return this->PACKET_SIZE;
}

const bool LinuxClientSocket::is_open() const
{
    return this->open;
}

void LinuxClientSocket::close()
{
    ::close(this->descriptor);
    this->open = false;
}

LinuxServerSocket::LinuxServerSocket(in_addr_t &ip_address, int port) : LinuxServerSocket(port)
{
    this->server_address.sin_addr.s_addr = ip_address;
}

LinuxServerSocket::LinuxServerSocket(int port)
{
    this->server_address.sin_family = AF_INET;
    this->server_address.sin_port = ::htons(port);
    this->server_address.sin_addr.s_addr = INADDR_ANY;

    int socket_descriptor = ::socket(AF_INET, SOCK_STREAM, 0);

    if (socket_descriptor == this->SYS_SOCKET_ERROR_VALUE)
    {
        throw ConnectionFailure();
    }

    this->descriptor = socket_descriptor;
}

void LinuxServerSocket::bind()
{
    int return_code = ::bind(
        this->descriptor, (struct sockaddr *)&(this->server_address),
        sizeof(this->server_address));

    if (return_code == this->SYS_SOCKET_ERROR_VALUE)
    {
        throw ConnectionFailure();
    }
}

void LinuxServerSocket::listen()
{
    int return_code = ::listen(this->descriptor, 5);

    if (return_code == this->SYS_SOCKET_ERROR_VALUE)
    {
        throw ConnectionFailure();
    }
}

void LinuxServerSocket::accept()
{
    int client_descriptor = ::accept(this->descriptor, nullptr, nullptr);

    if (client_descriptor == this->SYS_SOCKET_ERROR_VALUE)
    {
        throw ConnectionFailure();
    }

    this->client_descriptor = client_descriptor;
    this->open = true;
}

void LinuxServerSocket::recv(void *buffer, size_t size)
{
    if (size > this->get_packet_size())
    {
        throw PacketExceedMaxSizeException();
    }

    int recv_bytes = ::recv(this->client_descriptor, buffer, size, 0);

    if (recv_bytes == this->SYS_SOCKET_ERROR_VALUE)
    {
        throw PacketRecievingFailure();
    }
    else if (recv_bytes != size)
    {
        throw PacketDamagedException();
    }
}

const size_t LinuxServerSocket::get_packet_size() const
{
    return this->PACKET_SIZE;
}

const bool LinuxServerSocket::is_open() const
{
    return this->open;
}

void LinuxServerSocket::close()
{
    ::close(this->descriptor);
    this->open = false;
}

LinuxClientSocketFactory::LinuxClientSocketFactory(std::string &ip_address, int port)
{
    this->ip_address = ip_address;
    this->port = port;
}

std::shared_ptr<BaseClientSocket> LinuxClientSocketFactory::create()
{
    in_addr_t ip_address = ::inet_addr(this->ip_address.c_str());
    return std::make_shared<LinuxClientSocket>(LinuxClientSocket(ip_address, this->port));
}

LinuxServerSocketFactory::LinuxServerSocketFactory(int port)
{
    this->port = port;
}

std::shared_ptr<BaseServerSocket> LinuxServerSocketFactory::create()
{
    return std::make_shared<LinuxServerSocket>(LinuxServerSocket(this->port));
}
