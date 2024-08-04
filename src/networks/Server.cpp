#include "Server.hpp"

Server::Server(BaseServerSocketFactory &server_socket_factory)
{
    this->socket = server_socket_factory.create();
    this->buffer = std::make_unique<Buffer>(Buffer(this->socket->get_packet_size()));
}

Server::~Server()
{
    if (this->is_connected())
    {
        this->close_connection();
    }
}

const bool Server::is_connected() const
{
    return this->connection;
}

const size_t Server::get_max_allowed_file_name_size() const
{
    return this->socket->get_packet_size() - 1 - sizeof(size_t);
}

std::shared_ptr<FileInfo> Server::recv_file()
{
    std::shared_ptr<FileInfo> file = this->recv_file_info();
    this->recv_file_body(*file);

    return file;
}

void Server::recv_file_body(const FileInfo &file_info)
{
    std::ofstream file(file_info.name, std::ios::out | std::ios::binary);

    if (!file.is_open())
    {
        throw OpeningFileException();
    }

    const size_t buffer_size = this->buffer->get_size();
    size_t file_size = file_info.size;
    size_t written_byte_number;

    while (file_size > 0)
    {
        try
        {
            this->recv_in_buffer();
        }
        catch (std::exception exc)
        {
            std::remove(file_info.name.c_str());
            throw exc;
        }

        written_byte_number = file_size;
        if (file_size >= buffer_size)
        {
            written_byte_number = buffer_size;
        }

        file.write((char *)this->buffer->get_body(), written_byte_number);
        file_size -= written_byte_number;
    }

    file.close();
}

std::shared_ptr<FileInfo> Server::recv_file_info()
{
    this->buffer->clear();
    this->recv_in_buffer();
    return this->read_file_info_from_buffer();
}

std::shared_ptr<FileInfo> Server::read_file_info_from_buffer()
{
    std::string file_name = std::string((char *)this->buffer->get_body());

    if (file_name.size() > this->get_max_allowed_file_name_size())
    {
        throw FileNameExceedMaxLengthExcpetion();
    }

    size_t file_size = 0;
    this->buffer->read((void *)&file_size, sizeof(file_size), file_name.size() + 1);

    return std::make_shared<FileInfo>(FileInfo(file_name, file_size));
}

void Server::recv_in_buffer()
{
    this->socket->recv(this->buffer->get_body(), this->buffer->get_size());
}

void Server::establish_connection()
{
    this->socket->bind();
    this->socket->listen();
    this->socket->accept();
    this->connection = true;
}

void Server::close_connection()
{
    this->socket->close();
    this->connection = false;
}