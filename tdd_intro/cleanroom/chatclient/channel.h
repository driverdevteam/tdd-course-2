#pragma once
#include "ihandshake.h"
#include "socketwrapper.h"
#include "ichannel.h"
#include <string>

class Channel : public IChannel
{
public:
    explicit Channel(ISocketWrapperPtr wrapper, IHandshakePtr handshake)
        : m_wrapper(wrapper)
        , m_handshake(handshake)
    {}

    void Handshake(const std::string& nick)
    {
        m_handshake->Handshake(*this, nick);
    }

    void Send(const std::string& message)
    {
        m_wrapper->Write(message);
    }
    void Receive(std::string& message)
    {
        m_wrapper->Read(message);
    }

private:
    ISocketWrapperPtr m_wrapper;
    IHandshakePtr m_handshake;
};
