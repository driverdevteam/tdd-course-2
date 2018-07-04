#pragma once
#include <igui.h>
#include "ichannel.h"

class Chat
{
public:
    explicit Chat(IGui& gui, IChannel* channel);
    void start();

private:
    IGui& m_gui;
    IChannel* m_channel;
};
