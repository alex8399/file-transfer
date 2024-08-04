#include "Client.hpp"

Client::Client(BaseClientSocketFactory &client_socket_factory)
{
    this->socket = client_socket_factory.create();
    this->buffer = std::make_unique<Buffer>(Buffer(this->socket->get_packet_size()));
}

const size_t Client::get_max_allowed_file_name_size() const
{
    return this->socket->get_packet_size() - 1 - sizeof(size_t);
}

const bool Client::is_connected() const
{
    return this->connection;
}

void Client::establish_connection()
{
    this->socket->connect();
    this->connection = true;
}

std::shared_ptr<FileInfo> Client::send_file(const std::string &file_name)
{
    size_t file_size = this->get_file_size(file_name);
    std::shared_ptr<FileInfo> file_info = std::make_shared<FileInfo>(FileInfo(file_name, file_size));

    this->send_file_info(*file_info);
    this->send_file_body(*file_info);

    return file_info;
}

const size_t Client::get_file_size(const std::string &file_name)
{
    size_t file_size = 0;

    try
    {
        file_size = std::filesystem::file_size(file_name);
    }
    catch (std::filesystem::filesystem_error exc)
    {
        throw OpeningFileException();
    }

    return file_size;
}

void Client::send_file_info(const FileInfo &file_info)
{
    if (file_info.name.size() > this->get_max_allowed_file_name_size())
    {
        throw FileNameExceedMaxLengthExcpetion();
    }

    this->write_file_info_in_buffer(file_info);
    this->send_from_buffer();
}

void Client::send_file_body(const FileInfo &file_info)
{
    std::ifstream file(file_info.name, std::ios::out | std::ios::binary);

    if (!file.is_open())
    {
        throw OpeningFileException();
    }

    const size_t buffer_size = this->buffer->get_size();
    size_t file_size = file_info.size;
    size_t read_byte_number;

    while (file_size > 0)
    {
        read_byte_number = file_size;
        if (file_size >= buffer_size)
        {
            read_byte_number = buffer_size;
        }

        file.read((char *)this->buffer->get_body(), read_byte_number);
        this->send_from_buffer();
        file_size -= read_byte_number;
    }

    file.close();
}

void Client::send_from_buffer()
{
    this->socket->send(this->buffer->get_body(), this->buffer->get_size());
}

void Client::write_file_info_in_buffer(const FileInfo &file_info)
{
    this->buffer->clear();
    this->buffer->write(file_info.name.c_str(), file_info.name.size(), 0);
    this->buffer->write(&(file_info.size), sizeof(file_info.size), file_info.name.size() + 1);
}

void Client::close_connection()
{
    this->socket->close();
    this->connection = false;
}

Client::~Client()
{
    if (this->is_connected())
    {
        this->close_connection();
    }
}