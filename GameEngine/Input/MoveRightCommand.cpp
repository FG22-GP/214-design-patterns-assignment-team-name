#include "MoveRightCommand.h"
#include "../GameObjects/Player.h"

void MoveRightCommand::Execute()
{
    Player::getInstance().PlayerMovement(1);
}
