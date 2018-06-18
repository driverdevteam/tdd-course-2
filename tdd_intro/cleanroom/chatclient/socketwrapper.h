#pragma once
#include "ISocketWrapper.h"

class SocketWrapper : public ISocketWrapper
{
public:
    SocketWrapper();
    explicit SocketWrapper(SOCKET& other);
    ~SocketWrapper();

    void Bind(const std::string& addr, int16_t port);
    void Listen();
    SocketWrapper Accept();
    virtual SockPtr Connect(const std::string& addr, int16_t port) override;
    void Read(std::vector<char>& buffer);
    void Write(const std::vector<char>& buffer);

private:
    SOCKET m_socket;
};
