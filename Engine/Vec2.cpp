#include "Vec2.h"
#include "cmath"

Vec2::Vec2( float in_x, float in_y )
	:
	x(in_x),
	y(in_y)
{
}

Vec2 Vec2::operator+( const Vec2& rhs ) const
{
	return Vec2( x + rhs.x, y + rhs.y );
}

Vec2& Vec2::operator+=( const Vec2& rhs )
{
	return *this = *this + rhs;
}

Vec2 Vec2::operator-( const Vec2& rhs ) const
{
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2& Vec2::operator-=( const Vec2& rhs )
{
	return *this = *this - rhs;
}

Vec2 Vec2::operator*( float val ) const
{
	return Vec2( x * val, y * val );
}

Vec2 Vec2::operator*=( float val )
{
	return *this = *this * val;
}

float Vec2::GetSqrLenght() const
{
	return x * x + y * y;
}

float Vec2::GetLenght() const
{
	return std::sqrt( GetSqrLenght() );
}

Vec2 Vec2::GetNormalized() const
{
	const float len = GetLenght();
	if( len != 0.0f )
	{
		return *this * (1.0f / GetLenght());
	}
	return *this;
}

void Vec2::Normalize()
{
	*this = GetNormalized();
}

