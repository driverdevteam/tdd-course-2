#pragma once
#include <string>
#include <memory>

class Channel;
class IHandshake
{
public:
    virtual ~IHandshake(){}
    virtual std::string Handshake(Channel& channel, const std::string& nick) = 0;
};
using IHandshakePtr = std::shared_ptr<IHandshake>;
