#pragma once
#include <gmock/gmock.h>
#include "isocketwrapper.h"

class SocketWrapperMock : public ISocketWrapper
{
public:
    MOCK_METHOD2(Bind, void(const std::string& addr, int16_t port));
    MOCK_METHOD0(Listen, void());
    MOCK_METHOD0(Accept, ISocketWrapperPtr());
    MOCK_METHOD2(Connect, ISocketWrapperPtr(const std::string& addr, int16_t port));
    MOCK_METHOD1(Read, void(std::string& buffer));
    MOCK_METHOD1(Write, void(const std::string& buffer));
};
