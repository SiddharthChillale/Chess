#pragma once

class Vec2
{
public:
	Vec2() = default;
	Vec2( float in_x, float in_y );

	Vec2 operator+( const Vec2& rhs ) const;
	Vec2& operator+=( const Vec2& rhs );
	Vec2 operator-( const Vec2& rhs ) const;
	Vec2& operator-=( const Vec2& rhs );
	Vec2 operator*( float val ) const;
	Vec2 operator*=( float val );

	float GetSqrLenght() const;
	float GetLenght() const;
	Vec2 GetNormalized() const;
	void Normalize();
public:
	float x;
	float y;
};