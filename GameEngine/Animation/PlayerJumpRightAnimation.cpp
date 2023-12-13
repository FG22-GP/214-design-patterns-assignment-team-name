#include "PlayerJumpRightAnimation.h"

PlayerJumpRightAnimation::PlayerJumpRightAnimation()
{
    TimeBetweenFrames = 1.f;
    
    TexturePaths.emplace_back("img/PlayerSprites/PlayerRun3.png");
    
    CreateTextures();
}
