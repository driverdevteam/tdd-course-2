#include "chatutils.h"
#include "serverhandshake.h"


void PerformClientHandshake(Channel& channel, const std::string& login)
{
    std::string buffer;
    channel.Send(login + ":HELLO");
    channel.Receive(buffer);
}

void PerformServerHandshake(Channel& channel, const std::string& login)
{
    std::string buffer;
    channel.Receive(buffer);
    channel.Send(login + ":HELLO!");
}

Channel SetupServerChannel(ISocketWrapperPtr socket)
{
    socket->Bind(host, port);
    socket->Listen();
    IHandshakePtr handshake(new ServerHandshake());
    return Channel(socket->Accept(), handshake);
}

Channel SetupClientChannel(ISocketWrapperPtr socket)
{
    IHandshakePtr handshake(new ServerHandshake());
    return Channel(socket->Connect(host, port), handshake);
}

Channel StartSession(ISocketWrapperPtr socket)
{
    try
    {
        return SetupClientChannel(socket);
    }
    catch (const std::exception& )
    {
        //I'm server
    }
    return SetupServerChannel(socket);
}
