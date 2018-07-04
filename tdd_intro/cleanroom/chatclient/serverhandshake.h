#pragma once
#include "ihandshake.h"

class ServerHandshake : public IHandshake
{
public:
    ServerHandshake();

    virtual std::string Handshake(Channel& channel, const std::string& nick);
};
