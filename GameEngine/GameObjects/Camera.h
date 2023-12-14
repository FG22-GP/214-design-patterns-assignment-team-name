#pragma once
#include "../EngineClasses/Vector2.h"

class Camera
{
public:
    Vector2 Position;

    Vector2 GetRelativeLocation(Vector2 InLocation);
};
