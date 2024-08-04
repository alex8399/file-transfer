#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "SocketExceptions.hpp"
#include "SocketInterfaces.hpp"
#include "Buffer.hpp"
#include "../exceptions/Exceptions.hpp"
#include "FileInfo.hpp"

class Server
{
private:
    std::shared_ptr<BaseServerSocket> socket;
    std::unique_ptr<Buffer> buffer;
    bool connection = false;

    void recv_in_buffer();

    std::shared_ptr<FileInfo> recv_file_info();
    void recv_file_body(const FileInfo &file_info);

    std::shared_ptr<FileInfo> read_file_info_from_buffer();

public:
    Server(BaseServerSocketFactory &client_socket_factory);
    ~Server();

    std::shared_ptr<FileInfo> recv_file();

    const size_t get_max_allowed_file_name_size() const;

    void establish_connection();
    void close_connection();
    const bool is_connected() const;
};

#endif