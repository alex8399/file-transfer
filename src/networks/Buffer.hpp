#ifndef __BUFFER_HPP__
#define __BUFFER_HPP__

#include <memory>
#include <cstring>

#include "../exceptions/Exceptions.hpp"

class Buffer {
private:
    std::unique_ptr<char[]> body;
    size_t size;

    static const char ZERO_SYMBOL = '\0';

public:
    Buffer(size_t size);

    void * get_body();
    const size_t get_size() const;

    void write(const void *source, const size_t size, const size_t pos_in_buffer);
    void read(void *dest, const size_t size, const size_t pos_in_buffer);
    void clear();
};


#endif