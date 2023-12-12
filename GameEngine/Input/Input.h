#pragma once
#include "Command.h"

class Input
{
public:
    Command* MoveLeftAction;
    Command* MoveRightAction;
    Command* JumpAction;
    Command* QuitAction;

    void GetInput();
};
