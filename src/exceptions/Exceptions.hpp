#ifndef __EXCEPTIONS_HPP__
#define __EXCEPTIONS_HPP__

#include <exception>
#include <string>

static const char *error_default_message = "Non defined error";

class BaseException : public std::exception
{
public:
    const char *what() const noexcept override
    {
        const char *error_message = this->get_message();

        if (error_message == nullptr) {
            error_message = error_default_message;
        }

        return error_message;
    }

    virtual const char *get_message() const noexcept = 0;
    ~BaseException() = default;
};

class OpeningFileException : public BaseException
{

public:
    const char *get_message() const noexcept override
    {
        return "File can not be open or does not exist.";
    }
};

class BufferOverflowException : public BaseException
{

public:
    const char *get_message() const noexcept override
    {
        return "Buffer is overflow.";
    }
};


class FileNameExceedMaxLengthExcpetion : public BaseException
{

public:
    const char *get_message() const noexcept override
    {
        return "Length of file name exceeds maximum allowed size.";
    }
};


class FileCreationException : public BaseException
{

public:
    const char *get_message() const noexcept override
    {
        return "File can not be created.";
    }
};


#endif