#pragma once
#include "channel.h"

const std::string host = "localhost";
const int port = 4444;

void PerformClientHandshake(Channel& channel, const std::string& login);
void PerformServerHandshake(Channel& channel, const std::string& login);

Channel SetupServerChannel(ISocketWrapperPtr socket);
Channel SetupClientChannel(ISocketWrapperPtr socket);

Channel StartSession(ISocketWrapperPtr socket);
