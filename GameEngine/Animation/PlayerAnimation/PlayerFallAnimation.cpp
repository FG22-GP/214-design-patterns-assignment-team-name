#include "PlayerFallAnimation.h"

PlayerFallAnimation::PlayerFallAnimation()
{
    TimeBetweenFrames = 1.f;
    
    TexturePaths.emplace_back("img/PlayerSprites/PlayerRun4.png");
    
    CreateTextures();
}
