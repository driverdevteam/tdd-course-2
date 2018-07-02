#include "chatutils.h"


void ClientHandshake(Channel& channel, const std::string& login)
{
    std::string buffer;
    channel.Send(login + ":HELLO");
    channel.Receive(buffer);

}

void ServerHandshake(Channel& channel, const std::string& login)
{
    std::string buffer;
    channel.Receive(buffer);
    channel.Send(login + ":HELLO!");
}

Channel SetupServerChannel(ISocketWrapperPtr socket)
{
    socket->Bind(host, port);
    socket->Listen();
    return Channel(socket->Accept());
}

Channel SetupClientChannel(ISocketWrapperPtr socket)
{
    return Channel(socket->Connect(host, port));
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
