#ifndef __FILE_STRUCT_HPP__
#define __FILE_STRUCT_HPP__

#include <string>

struct FileInfo {
public:
    const std::string name;
    const size_t size;

    FileInfo(const std::string &name, const size_t size) : name(name), size(size) {}
};


using FileInfo = struct FileInfo;

#endif