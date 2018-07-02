#pragma once
#include "channel.h"

const std::string host = "localhost";
const int port = 4444;

void ClientHandshake(Channel& channel, const std::string& login);
void ServerHandshake(Channel& channel, const std::string& login);

Channel SetupServerChannel(ISocketWrapperPtr socket);
Channel SetupClientChannel(ISocketWrapperPtr socket);

Channel StartSession(ISocketWrapperPtr socket);
