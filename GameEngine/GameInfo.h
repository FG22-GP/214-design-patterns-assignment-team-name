#pragma once
#include "Window.h"

class GameInfo
{
private:

    static GameInfo* instancePointer;

    GameInfo() = default;

public:
    Window* window;
    
    GameInfo(const GameInfo& obj) = delete;

    static GameInfo* GetInstance();
    
    void SetWindow(Window* window);

    static void Cleanup();
    
};
