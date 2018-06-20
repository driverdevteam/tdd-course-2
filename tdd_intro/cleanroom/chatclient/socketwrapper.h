#pragma once
#include <cstdint>

class SocketWrapper
{
public:
    SocketWrapper();
    explicit SocketWrapper(SOCKET& other);
    ~SocketWrapper();

    void Bind(const std::string& addr, int16_t port);
    void Listen();
    SocketWrapper Accept();
    SocketWrapper Connect(const std::string& addr, int16_t port);
    void Read(std::string& buffer);
    void Write(const std::string& buffer);

private:
    SOCKET m_socket;
};
