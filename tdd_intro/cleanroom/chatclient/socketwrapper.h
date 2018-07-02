#pragma once
#include <cstdint>
#include <windows.h>
#include <memory>
#include <string>

class ISocketWrapper;
using ISocketWrapperPtr = std::shared_ptr<ISocketWrapper>;

class ISocketWrapper
{
public:
    virtual void Bind(const std::string& addr, int16_t port) = 0;
    virtual void Listen()= 0;
    virtual ISocketWrapperPtr Accept() = 0;
    virtual ISocketWrapperPtr Connect(const std::string& addr, int16_t port)= 0;
    virtual void Read(std::string& buffer)= 0;
    virtual void Write(const std::string& buffer)= 0;
};

class SocketWrapper : public ISocketWrapper
{
public:
    SocketWrapper();
    explicit SocketWrapper(SOCKET& other);
    ~SocketWrapper();
    void Bind(const std::string& addr, int16_t port);
    void Listen();
    ISocketWrapperPtr Accept();
    ISocketWrapperPtr Connect(const std::string& addr, int16_t port);
    void Read(std::string& buffer);
    void Write(const std::string& buffer);

private:
    SOCKET m_socket;
};
