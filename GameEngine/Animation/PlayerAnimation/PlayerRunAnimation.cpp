#include "PlayerRunAnimation.h"

PlayerRunAnimation::PlayerRunAnimation()
{
    TimeBetweenFrames = 0.1f;
    
    TexturePaths.emplace_back("img/PlayerSprites/PlayerRun1.png");
    TexturePaths.emplace_back("img/PlayerSprites/PlayerRun2.png");
    TexturePaths.emplace_back("img/PlayerSprites/PlayerRun3.png");
    TexturePaths.emplace_back("img/PlayerSprites/PlayerRun4.png");
    
    CreateTextures();
}
