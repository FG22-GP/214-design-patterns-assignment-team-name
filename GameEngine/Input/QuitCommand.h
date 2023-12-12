#pragma once
#include "Command.h"

class QuitCommand : public Command
{
public:
    void Execute() override;
};
