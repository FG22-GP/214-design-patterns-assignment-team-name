#pragma once
#include "Vector2.h"
#include "Texture.h"

class Sprite
{
public:
    Sprite();

    void Reset();

    Texture* texture;
    Vector2 position;
    Vector2 size;
    bool isCollider;
    bool flip = false;
};
