#include "PlayerJumpAnimation.h"

PlayerJumpAnimation::PlayerJumpAnimation()
{
    TimeBetweenFrames = 1.f;
    
    TexturePaths.emplace_back("img/PlayerSprites/PlayerRun3.png");
    
    CreateTextures();
}
