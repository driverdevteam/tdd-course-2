#pragma once
#include "socketwrapper.h"
#include <string>

class Channel
{
public:
    explicit Channel(ISocketWrapperPtr wrapper): m_wrapper(wrapper)  {}
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
};
