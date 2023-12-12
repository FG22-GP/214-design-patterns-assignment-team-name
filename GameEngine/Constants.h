#pragma once
#include <string>

class Constants
{
public:
    static constexpr int SCREEN_WIDTH = 1024;
    static constexpr int SCREEN_HEIGHT = 768;

    inline static const std::string PLAYERSPRITEFILEPATH {"img/pikachu.png"};
    inline static const std::string WALLSPRITEFILEPATH {"img/Wall.png"};
    inline static const std::string FONTFILEPATH {"font/lazy.ttf"};
};
