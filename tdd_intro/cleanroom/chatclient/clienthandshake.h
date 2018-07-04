#pragma once
#include "ihandshake.h"



class ClientHandshake : public IHandshake
{
public:
    ClientHandshake();

    virtual std::string Handshake(Channel& channel, const std::string& nick);
};
