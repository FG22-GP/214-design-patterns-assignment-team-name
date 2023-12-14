#include "MoveLeftCommand.h"
#include "../GameObjects/Player.h"

void MoveLeftCommand::Execute()
{
    Player::getInstance().PlayerMovement(-1);
}
