#pragma once
#include <string>

class IGui
{
public:
    virtual ~IGui() {}
    virtual void PrintPrompt() = 0;
    virtual std::string ReadMessage() = 0;
    virtual void DisplayMessage(const std::string& text) = 0;
};
