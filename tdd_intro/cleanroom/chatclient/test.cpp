#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "socketwrapper.h"
#include "chatutils.h"

using namespace testing;
/*
Implement chat application, that communicates via TCP sockets.
 There is list of requirenments to this application:
 * It receives user nickname through commandline arguments on start
 * It runs only for two clients
 * On start it checks if port port is bound
    * if it is - connects to other client
    * if not - binds a port and waits for inbound connection
        * message "No one is here..." is displayed in UI
 * After establishing connection - handshake is performed:
    * client writes message with it's nickname and ':HELLO!' string to socket ("metizik:HELLO!")
    * server responses with it's nickname and ':HELLO!' magic ("user:HELLO!")
        * if server receives malformated message - it drops connection with this client
        * if client receives malformated message - it drops connection and exits
            * Error message is shown
    * Listening socket must be closed
        (i) More than one client is not allowed to connect

 * It must send messages via created connection, until it is dropped
    * Application outputs "me: " prefix for user input
    * User inputs message through console interface and presses ENTER
    * Text message is sent to socket
 * It must receive messages via created connection, until it is dropped
    * Message received through socket
    * Line with message and '@friend_name: ' prefix is displayed ("metizik: Hello!")
 * END of message is determined by '\0' byte
 * When connection is dropped by one of users
    * "You are alone now" message is displayed to user
    * Application exits

  (i) Client starts dialog

 OPTIONAL requirement:
    * If user enters '!exit!' message, application must close connection and exit
    * If user runs app with 'me' nickname - error with text "Username me is reserved and can not be used"  is displayed and application exits
*/


class MockSocketWrapper : public ISocketWrapper
{
public:
    MOCK_METHOD2(Bind, void(const std::string& addr, int16_t port));
    MOCK_METHOD0(Listen, void());
    MOCK_METHOD0(Accept, ISocketWrapperPtr());
    MOCK_METHOD2(Connect, ISocketWrapperPtr(const std::string& addr, int16_t port));
    MOCK_METHOD1(Read, void(std::string& buffer));
    MOCK_METHOD1(Write, void(const std::string& buffer));

};

typedef std::shared_ptr<MockSocketWrapper> MockSocketWrapperPtr;

TEST(SocketWrapperTest, Sending)
{
    MockSocketWrapperPtr socket = std::make_shared<MockSocketWrapper>();
    Channel channel(socket);

    EXPECT_CALL(*socket, Write("Hello")).Times(1);
    channel.Send("Hello");
}

TEST(SocketWrapperTest, Receiving)
{
    MockSocketWrapperPtr socket = std::make_shared<MockSocketWrapper>();
    Channel channel(socket);

    std::string buffer;
    EXPECT_CALL(*socket, Read(_)).WillOnce(SetArgReferee<0>("Hello"));
    channel.Receive(buffer);

    EXPECT_EQ("Hello", buffer);
}

TEST(SocketWrapperTest, ClientHandshake)
{
    MockSocketWrapperPtr socket = std::make_shared<MockSocketWrapper>();
    Channel channel(socket);
    InSequence sequence;
    EXPECT_CALL(*socket, Write("metizik:HELLO")).Times(1);
    EXPECT_CALL(*socket, Read(_)).Times(1);
    ClientHandshake(channel, "metizik");
}

TEST(SocketWrapperTest, ServerHandshake)
{
    MockSocketWrapperPtr socket = std::make_shared<MockSocketWrapper>();
    Channel channel(socket);
    EXPECT_CALL(*socket, Read(_)).Times(1);
    EXPECT_CALL(*socket, Write("user:HELLO!")).Times(1);
    ServerHandshake(channel, "user");
}

TEST(SocketWrapperTest, StartServerChannel)
{
    MockSocketWrapperPtr socket = std::make_shared<MockSocketWrapper>();
    EXPECT_CALL(*socket, Bind(host, port)).Times(1);
    EXPECT_CALL(*socket, Listen()).Times(1);
    EXPECT_CALL(*socket, Accept()).WillOnce(testing::Return(nullptr));

    SetupServerChannel(socket);
}

TEST(SocketWrapperTest, StartClientChannel)
{
    MockSocketWrapperPtr socket = std::make_shared<MockSocketWrapper>();
    EXPECT_CALL(*socket, Connect(host, port)).WillOnce(testing::Return(nullptr));

    SetupClientChannel(socket);
}

TEST(SocketWrapperTest, StartSession_SetupServer)
{
    MockSocketWrapperPtr socket = std::make_shared<MockSocketWrapper>();

    EXPECT_CALL(*socket, Connect(host, port)).WillOnce(testing::Throw(std::exception("")));
    EXPECT_CALL(*socket, Bind(host, port)).Times(1);
    EXPECT_CALL(*socket, Listen()).Times(1);
    EXPECT_CALL(*socket, Accept()).WillOnce(testing::Return(nullptr));

    EXPECT_NO_THROW(StartSession(socket));
}

