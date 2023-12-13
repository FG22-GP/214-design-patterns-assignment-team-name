#include "PlayerFallRightAnimation.h"

PlayerFallRightAnimation::PlayerFallRightAnimation()
{
    TimeBetweenFrames = 1.f;
    
    TexturePaths.emplace_back("img/PlayerSprites/PlayerRun4.png");
    
    CreateTextures();
}
