#pragma once
#include "Command.h"
#include "MoveLeftCommand.h"
#include "MoveRightCommand.h"
#include "QuitCommand.h"
#include "JumpCommand.h"

class Input
{
    MoveLeftCommand moveLeft{};
    MoveRightCommand moveRight{};
    JumpCommand jump{};
    QuitCommand quitting{};
    
public:
    Input();
    
    Command* MoveLeftAction;
    Command* MoveRightAction;
    Command* JumpAction;
    Command* QuitAction;

    void GetInput();
};
