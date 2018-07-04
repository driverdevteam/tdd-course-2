#include "chat.h"

Chat::Chat(IGui& gui, IChannel* channel)
    : m_gui(gui)
    , m_channel(channel)
{

}

void Chat::start()
{
    m_gui.PrintPrompt();
    m_channel->Send(m_gui.ReadMessage());
    std::string outputText;
    m_channel->Receive(outputText);
    m_gui.DisplayMessage(outputText);
}
