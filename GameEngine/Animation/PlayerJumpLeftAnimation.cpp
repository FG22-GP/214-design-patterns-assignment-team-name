#include "PlayerJumpLeftAnimation.h"

PlayerJumpLeftAnimation::PlayerJumpLeftAnimation()
{
    TimeBetweenFrames = 1.f;
    
    TexturePaths.emplace_back("img/PlayerSprites/PlayerRun3Left.png");
    
    CreateTextures();
}
