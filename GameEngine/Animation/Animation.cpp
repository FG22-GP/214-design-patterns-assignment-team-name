#include "Animation.h"
#include <SDL_timer.h>
#include "../EngineClasses/Engine.h"

void Animation::CreateTextures()
{
    Engine* engine = Engine::GetInstance();
    for (auto Path = TexturePaths.begin(); Path != TexturePaths.end(); ++Path)
    {
        Textures.emplace_back(Texture{engine->GetWindow()->renderer, *Path});
    }
}

Texture* Animation::GetTexture()
{
    float CurrentTime = (float)SDL_GetTicks() / 1000.f;
    float Diff = CurrentTime - LastTime;
    TimeSinceLastUpdate += Diff;
    LastTime = CurrentTime;
    
    if(TimeSinceLastUpdate > TimeBetweenFrames)
    {
        TimeSinceLastUpdate = 0.f;
        
        CurrentTextureIndex++;
        if(CurrentTextureIndex >= Textures.size())
        {
            CurrentTextureIndex = 0;
        }
    }
    
    auto Iterator = Textures.begin();
    std::advance(Iterator, CurrentTextureIndex);
    return &*Iterator;
}
