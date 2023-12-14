#pragma once
#include <complex>

struct Vector2
{
    float x, y;
    //Constructor
    Vector2(float x = 0, float y = 0)
    {
        this->x = x;
        this->y = y;
    }

    //Makes this Vector2 equal to the right-hand side Vector2
    Vector2 operator=(const Vector2& b)
    {
        this->x = b.x;
        this->y = b.y;
        return *this;
    }

#pragma region "Basic math operator overloads"
    Vector2 operator+(const Vector2& b) const
    {
        Vector2 c;
        c.x = this->x + b.x;
        c.y = this->y + b.y;
        return c;
    }
    Vector2 operator-(const Vector2& b) const
    {
        Vector2 c;
        c.x = this->x - b.x;
        c.y = this->y - b.y;
        return c;
    }
    Vector2 operator*(const float& b) const
    {
        Vector2 c;
        c.x = this->x * b;
        c.y = this->y * b;
        return c;
    }
    Vector2 operator/(const float& b) const
    {
        Vector2 c;
        c.x = this->x / b;
        c.y = this->y / b;
        return c;
    }
    Vector2 operator+=(const Vector2& b)
    {
        this->x += b.x;
        this->y += b.y;
        return *this;
    }
    Vector2 operator-=(const Vector2& b)
    {
        this->x -= b.x;
        this->y -= b.y;
        return *this;
    }
    Vector2 operator*=(const float& b)
    {
        this->x *= b;
        this->y *= b;
        return *this;
    }
    Vector2 operator/=(const float& b)
    {
        this->x /= b;
        this->y /= b;
        return *this;
    }
    float magnitude()
    {
        return std::sqrt(x*x+y*y);
    }
#pragma endregion

#pragma region "Boolean Operator overloads"
    bool operator==(const Vector2& b) const
    {
        if(this->x == b.x && this->y == b.y)
        {
            return true;
        }
        return false;
    }
    bool operator!=(const Vector2& b) const
    {
        if(this->x != b.x || this->y != b.y)
        {
            return true;
        }
        return false;
    }
#pragma endregion
    
};
