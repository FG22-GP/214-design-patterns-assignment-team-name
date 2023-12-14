#include "JumpCommand.h"
#include "../GameObjects/Player.h"

void JumpCommand::Execute()
{
    Player::getInstance().Jump();
}
