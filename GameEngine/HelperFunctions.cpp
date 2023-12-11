#include "HelperFunctions.h"
#include "Vector2.h"

float HelperFunctions::DotProduct(Vector2 V1, Vector2 V2)
{
	return V1.x * V2.x + V1.y * V2.y;
}

float HelperFunctions::Length(Vector2 InVector)
{
	return std::sqrt(InVector.x * InVector.x + InVector.y * InVector.y);
}

Vector2 HelperFunctions::Normalize(Vector2 InVector)
{
	return InVector / Length(InVector);
}

float HelperFunctions::Clamp(float Num, float Min, float Max)
{
	if(Num < Min) return Min;
	if(Num > Max) return Max;
	return Num;
}

bool HelperFunctions::CheckIntersection(Vector2 Pos1, Vector2 Size1, Vector2 Pos2, Vector2 Size2)
{
	Vector2 Middle1 = Pos1 + Vector2{Size1.x / 2.f, Size1.y / 2.f};
	Vector2 Middle2 = Pos2 + Vector2{Size2.x / 2.f, Size2.y / 2.f};
	
	float XDistance = std::abs(Middle1.x - Middle2.x);
	float YDistance = std::abs(Middle1.y - Middle2.y);
	
	float MaxXWithinBounds = Size1.x / 2.f + Size2.x / 2.f;
	float MaxYWithinBounds = Size1.y / 2.f + Size2.y / 2.f;

	return MaxXWithinBounds > XDistance && MaxYWithinBounds > YDistance;
}

Vector2 HelperFunctions::GetIntersectionPointAABB(Vector2 Pos1, Vector2 Size1, Vector2 Pos2, Vector2 Size2)
{
	Vector2 Middle1 = Pos1 + Vector2{Size1.x / 2.f, Size1.y / 2.f};
	Vector2 Middle2 = Pos2 + Vector2{Size2.x / 2.f, Size2.y / 2.f};

	//vertical lines of first AABB
	float VerticalMinXAxis1 = Middle1.x - Size1.x / 2.f;
	float VerticalMaxXAxis1 = Middle1.x + Size1.x / 2.f;
	float VerticalStart1 = Middle1.y + Size1.y / 2.f;
	float VerticalEnd1 = Middle1.y - Size1.y / 2.f;

	//horizontal lines of first AABB
	float HorizontalMinYAxis1 = Middle1.y - Size1.y / 2.f;
	float HorizontalMaxYAxis1 = Middle1.y + Size1.y / 2.f;
	float HorizontalStart1 = Middle1.x - Size1.x / 2.f;
	float HorizontalEnd1 = Middle1.x + Size1.x / 2.f;
	
	//horizontal lines of second AABB
	float HorizontalMinYAxis2 = Middle2.y - Size2.y / 2.f;
	float HorizontalMaxYAxis2 = Middle2.y + Size2.y / 2.f;
	float HorizontalStart2 = Middle2.x - Size2.x / 2.f;
	float HorizontalEnd2 = Middle2.x + Size2.x / 2.f;

	//L = left, R = right, T = top, B = bottom
	bool L1T2 = CheckIntersectionLineSeg(VerticalMinXAxis1, VerticalStart1, VerticalEnd1, HorizontalMinYAxis2, HorizontalStart2, HorizontalEnd2);
	bool L1B2 = CheckIntersectionLineSeg(VerticalMinXAxis1, VerticalStart1, VerticalEnd1, HorizontalMaxYAxis2, HorizontalStart2, HorizontalEnd2);
	bool R1T2 = CheckIntersectionLineSeg(VerticalMaxXAxis1, VerticalStart1, VerticalEnd1, HorizontalMinYAxis2, HorizontalStart2, HorizontalEnd2);
	bool R1B2 = CheckIntersectionLineSeg(VerticalMaxXAxis1, VerticalStart1, VerticalEnd1, HorizontalMaxYAxis2, HorizontalStart2, HorizontalEnd2);

	//Right collision full contact
	if(R1T2 && R1B2)
	{
		return {HorizontalEnd1, Middle1.y};
	}
	//Left collision full contact
	if(L1T2 && L1B2)
	{
		return {HorizontalStart1, Middle1.y};
	}

	//Right collision top contact only
	if(R1T2 && HorizontalMaxYAxis1 > HorizontalMinYAxis2 + 20)
	{
		return {HorizontalEnd1, Middle1.y};
	}
	//Left collision top contact only
	if(L1T2 && HorizontalMaxYAxis1 > HorizontalMinYAxis2 + 20)
	{
		return {HorizontalStart1, Middle1.y};
	}

	//Bottom collision
	if(R1T2 || L1T2)
	{
		return {Middle1.x, HorizontalMaxYAxis1};
	}

	//Right collision bottom only
	if(R1B2 && HorizontalMinYAxis1 < HorizontalMaxYAxis2 - 20)
	{
		return {HorizontalEnd1, Middle1.y};
	}
	//Left collision bottom only
	if(L1B2 && HorizontalMinYAxis1 < HorizontalMaxYAxis2 - 20)
	{
		return {HorizontalStart1, Middle1.y};
	}

	//Top collision
	if(R1B2 || L1B2)
	{
		return {Middle1.x, HorizontalMinYAxis1};
	}
	
	return Middle1;
}

bool HelperFunctions::CheckIntersectionLineSeg(float Line1XAxis, float Line1YStart, float Line1YEnd, float Line2YAxis, float Line2XStart, float Line2XEnd)
{
	return (Line1XAxis > Line2XStart && Line1XAxis < Line2XEnd) && (Line2YAxis < Line1YStart && Line2YAxis > Line1YEnd);
}
