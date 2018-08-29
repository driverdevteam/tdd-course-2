#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <exception>
#include <vector>
#include <string>
#include <sstream>
#include <memory>

#include "SocketWrapper.h"

namespace
{
    std::string GetExceptionString(const std::string& message, int errorCode)
    {
        return message + " " + std::to_string(errorCode) + "\n";
    }
}

SocketWrapper::SocketWrapper()
    : m_socket(INVALID_SOCKET)
{
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_socket == INVALID_SOCKET)
    {
        throw std::runtime_error(GetExceptionString("Failed to create socket to listen on.", WSAGetLastError()));
    }
}

SocketWrapper::SocketWrapper(SOCKET & other)
    : m_socket(other)
{
}

SocketWrapper::~SocketWrapper()
{
    closesocket(m_socket);
}

void SocketWrapper::Bind(const std::string& addr, int16_t port)
{
    sockaddr_in addres;
    addres.sin_family = AF_INET;
    addres.sin_addr.s_addr = inet_addr(addr.data());
    addres.sin_port = htons(port);
    if (bind(m_socket, reinterpret_cast<sockaddr*>(&addres), sizeof(addres)) == SOCKET_ERROR)
    {
        throw std::runtime_error(GetExceptionString("Failed to bind socket to address.", WSAGetLastError()));
    }
}

void SocketWrapper::Listen()
{
    if (listen(m_socket, SOMAXCONN) == SOCKET_ERROR)
    {
        throw std::runtime_error(GetExceptionString("Failed to listen on socket.", WSAGetLastError()));
    }
}

ISocketWrapperPtr SocketWrapper::Accept()
{
    SOCKET other = accept(m_socket, nullptr, nullptr);
    if (other == INVALID_SOCKET)
    {
        throw std::runtime_error(GetExceptionString("Failed to connect to client.", WSAGetLastError()));
    }
    return ISocketWrapperPtr(new SocketWrapper(other));
}

ISocketWrapperPtr SocketWrapper::Connect(const std::string& addr, int16_t port)
{
    sockaddr_in addres;
    addres.sin_family = AF_INET;
    addres.sin_addr.s_addr = inet_addr(addr.data());
    addres.sin_port = htons(port);
    SOCKET other = connect(m_socket, reinterpret_cast<sockaddr*>(&addres), sizeof(addres));
    if (other == INVALID_SOCKET)
    {
        throw std::runtime_error(GetExceptionString("Failed to connect to server.", WSAGetLastError()));
    }
    return ISocketWrapperPtr(new SocketWrapper(other));
}

void SocketWrapper::Read(std::string& buffer)
{
    std::vector<char> bufferTmp;
    bufferTmp.resize(buffer.size());
    if (SOCKET_ERROR == recv(m_socket, bufferTmp.data(), static_cast<int>(bufferTmp.size()), 0))
    {
        throw std::runtime_error(GetExceptionString("Failed to connect to server.", WSAGetLastError()));
    }
    buffer.assign(bufferTmp.begin(), bufferTmp.end());
}

void SocketWrapper::Write(const std::string& buffer)
{
    send(m_socket, buffer.data(), static_cast<int>(buffer.size()), 0);
}
