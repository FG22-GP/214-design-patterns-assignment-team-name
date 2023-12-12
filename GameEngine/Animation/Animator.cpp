#include "Animator.h"

Animator::Animator(Sprite* InSprite)
{
    MySprite = InSprite;
}

void Animator::UpdateSprite()
{
    MySprite->texture = Animations[CurrentAnimation].GetTexture();
}
