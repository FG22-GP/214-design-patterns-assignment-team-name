#include "Sprite.h"

#include "Vector2.h"

Sprite::Sprite()
{
    texture = nullptr;
    position = Vector2{ 0.0, 0.0 };
    size = Vector2{ 0.0, 0.0 };
    isCollider = false;
}


void Sprite::Reset() {
    texture = nullptr;
    position = Vector2{ 0.0, 0.0 };
    size = Vector2{ 0.0, 0.0 };
    isCollider = false;
}