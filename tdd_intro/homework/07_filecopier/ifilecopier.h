#pragma once
class IFileCopier
{
public:
    virtual void copy(const std::string& src, const std::string& dst) = 0;
};
