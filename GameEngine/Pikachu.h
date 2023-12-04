#pragma once
#include <SDL_render.h>

#include "GameInfo.h"


class Pikachu
{
private:
    const char* pikachuImagePath{"img/pikachu.png"};
    GameInfo* gameInfoInstance = GameInfo::GetInstance();

    void LoadTexture();

public:
    Pikachu()
    {
        pik_x = pik_y = 0;
        pik_w = pik_h = 200;
        
        
        LoadTexture();
    }

    ~Pikachu()
    {
    }

    // All data related to pikachu
    SDL_Texture* pikachu; // The final optimized image
    bool pikachuMoveRight;
    int pik_x, pik_y;
    int pik_w, pik_h;

    void HandleInput(const SDL_Event& event);
    
    void MoveLeft();

    void MoveRight();

    void Update();

    void Draw();
};
