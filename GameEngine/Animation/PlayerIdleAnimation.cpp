#include "PlayerIdleAnimation.h"

PlayerIdleAnimation::PlayerIdleAnimation()
{
    TimeBetweenFrames = 1.f;
    
    TexturePaths.emplace_back("img/PlayerSprites/PlayerIdle1.png");
    TexturePaths.emplace_back("img/PlayerSprites/PlayerIdle2.png");
    
    CreateTextures();
}
