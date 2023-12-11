#pragma once
#include "Vector2.h"

class HelperFunctions
{
public:
    static float DotProduct(Vector2 V1, Vector2 V2);
    static float Length(Vector2 InVector);
    static Vector2 Normalize(Vector2 InVector);

    static float Clamp(float Num, float Min, float Max);
    
    static bool CheckIntersection(Vector2 Pos1, Vector2 Size1, Vector2 Pos2, Vector2 Size2);
    static Vector2 GetIntersectionPointAABB(Vector2 Pos1, Vector2 Size1, Vector2 Pos2, Vector2 Size2);
    static bool CheckIntersectionLineSeg(float Line1XAxis, float Line1YStart, float Line1YEnd, float Line2YAxis, float Line2XStart, float Line2XEnd);
};
