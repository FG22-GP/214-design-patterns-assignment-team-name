#include "JumpCommand.h"
#include "../Player.h"

void JumpCommand::Execute()
{
    Player::getInstance().Jump();
}
