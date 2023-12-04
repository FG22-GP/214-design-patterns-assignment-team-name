#include "GameInfo.h"

GameInfo* GameInfo::instancePointer = nullptr;

GameInfo* GameInfo::GetInstance()
{
    if (instancePointer == nullptr)
    {
        instancePointer = new GameInfo();
        return instancePointer;
    }
    else
    {
        return instancePointer;
    }
}

void GameInfo::SetWindow(Window* window)
{
    this->window = window;
}

void GameInfo::Cleanup()
{
    delete instancePointer;
    instancePointer = nullptr;
}
