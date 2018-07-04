#ifndef ICHANNEL_H
#define ICHANNEL_H
#include "string"



class IChannel
{
public:
    ~IChannel() {}
    virtual void Handshake(const std::string& nick) = 0;
    virtual void Send(const std::string& message) = 0;
    virtual void Receive(std::string& message) = 0;
};
#endif // ICHANNEL_H
