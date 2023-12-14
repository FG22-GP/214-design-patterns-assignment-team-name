#pragma once
#include <list>

#include "../EngineClasses/Sprite.h"

class Animation
{
    float LastTime = 0.f;
    float TimeSinceLastUpdate = 0.f;
    
    int CurrentTextureIndex = 0;

protected:
    void CreateTextures();
    
public:
    float TimeBetweenFrames = 0.5f;
    
    std::list<std::string> TexturePaths;

    std::list<Texture> Textures;
    Texture* GetTexture();
};
