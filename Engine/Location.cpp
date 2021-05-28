#include "Location.h"

Location::Location( int in_x, int in_y )
{
	x = in_x;
	y = in_y;
}

bool Location::operator==( const Location& rhs ) const
{
	return (x == rhs.x) && (y == rhs.y);
}

bool Location::operator!=( const Location& rhs ) const
{
	return !(*this == rhs);
}

Location Location::operator+( const Location& rhs ) const
{
	return Location(x + rhs.x, y + rhs.y);
}

Location& Location::operator+=( const Location& rhs )
{
	return *this = *this + rhs;
}

Location Location::operator-( const Location& rhs ) const
{
	return Location( x - rhs.x, y - rhs.y );
}

Location& Location::operator-=( const Location& rhs )
{
	return *this = *this - rhs;
}

Location Location::operator*( int rhs ) const
{
	return Location( x * rhs, y * rhs );
}

Location& Location::operator*=( int rhs )
{
	return *this = *this * rhs;
}

Location Location::operator/( int rhs ) const
{
	return Location( x / rhs, y / rhs );
}

Location& Location::operator/=( int rhs )
{
	return *this = *this / rhs;
}
