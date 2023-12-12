#include "MoveRightCommand.h"
#include "../Player.h"

void MoveRightCommand::Execute()
{
    Player::getInstance().PlayerMovement(1);
}
