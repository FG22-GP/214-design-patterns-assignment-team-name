#include "MoveLeftCommand.h"
#include "../Player.h"

void MoveLeftCommand::Execute()
{
    Player::getInstance().PlayerMovement(-1);
}
