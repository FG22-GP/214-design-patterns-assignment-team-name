#include "QuitCommand.h"
#include "../EngineClasses/Engine.h"

void QuitCommand::Execute()
{
    Engine::GetInstance()->quit = true;
}
