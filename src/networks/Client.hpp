#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "SocketExceptions.hpp"
#include "SocketInterfaces.hpp"
#include "FileInfo.hpp"
#include "Buffer.hpp"
#include "../exceptions/Exceptions.hpp"

class  Client {
private:
    std::shared_ptr<BaseClientSocket> socket;
    std::unique_ptr<Buffer> buffer;
    bool connection = false;

    void send_from_buffer();
    void write_file_info_in_buffer(const FileInfo &file_info);
    void send_file_info(const FileInfo &file_info);
    void send_file_body(const FileInfo &file_info);

    static const size_t get_file_size(const std::string &file_name);

public:
    Client(BaseClientSocketFactory &client_socket_factory);
    ~Client();

    void establish_connection();
    void close_connection();

    std::shared_ptr<FileInfo> send_file(const std::string &file_path);

    const bool is_connected() const;

    const size_t get_max_allowed_file_name_size() const;
};



#endif