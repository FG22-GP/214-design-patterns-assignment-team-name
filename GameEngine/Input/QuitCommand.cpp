#include "QuitCommand.h"
#include "../Engine.h"
#include "../Player.h"

void QuitCommand::Execute()
{
    Engine::GetInstance()->quit = true;
}
