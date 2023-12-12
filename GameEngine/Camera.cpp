#include "Camera.h"

Vector2 Camera::GetRelativeLocation(Vector2 InLocation)
{
    return InLocation - Position;
}
