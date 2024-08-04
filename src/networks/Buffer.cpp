#include "Buffer.hpp"

Buffer::Buffer(size_t size)
{
    this->size = size;
    this->body = std::make_unique<char[]>(size);
}

void *Buffer::get_body()
{
    return this->body.get();
}

const size_t Buffer::get_size() const
{
    return this->size;
}

void Buffer::write(const void *source, const size_t size, const size_t pos_in_buffer)
{
    if (pos_in_buffer + size > this->size)
    {
        throw BufferOverflowException();
    }

    std::memcpy(((char *) this->get_body()) + pos_in_buffer, source, size);
}

void Buffer::read(void *dest, const size_t size, const size_t pos_in_buffer)
{
    if (pos_in_buffer + size > this->size)
    {
        throw BufferOverflowException();
    }

    std::memcpy((void *) dest, ((char *) this->get_body()) + pos_in_buffer, size);
}

void Buffer::clear()
{
    char *buffer_ptr = (char *)this->get_body();
    for (size_t ind = 0; ind != this->get_size(); ++ind)
    {
        std::memcpy((void *)(buffer_ptr + ind), &(this->ZERO_SYMBOL), sizeof(this->ZERO_SYMBOL));
    }
}
