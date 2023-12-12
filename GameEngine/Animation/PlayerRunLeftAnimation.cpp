#include "PlayerRunLeftAnimation.h"

PlayerRunLeftAnimation::PlayerRunLeftAnimation()
{
    TimeBetweenFrames = 0.1f;
    
    TexturePaths.emplace_back("img/PlayerSprites/PlayerRun1Left.png");
    TexturePaths.emplace_back("img/PlayerSprites/PlayerRun2Left.png");
    TexturePaths.emplace_back("img/PlayerSprites/PlayerRun3Left.png");
    TexturePaths.emplace_back("img/PlayerSprites/PlayerRun4Left.png");
    
    CreateTextures();
}
