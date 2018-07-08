#pragma once

using StringVector = std::vector<std::string>;
class IFileSystem
{
public:
    virtual bool isExist(const std::string& path) = 0;
    virtual StringVector getChildList(const std::string& path) = 0;
    virtual bool isDirectory(const std::string& path) = 0;
    virtual void copy(const std::string& src, const std::string& dst) = 0;
};
