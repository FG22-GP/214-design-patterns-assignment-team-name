#include "PlayerFallLeftAnimation.h"

PlayerFallLeftAnimation::PlayerFallLeftAnimation()
{
    TimeBetweenFrames = 1.f;
    
    TexturePaths.emplace_back("img/PlayerSprites/PlayerRun4Left.png");
    
    CreateTextures();
}
