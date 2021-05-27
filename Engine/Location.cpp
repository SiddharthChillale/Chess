#include "Location.h"

Location::Location( int in_x, int in_y )
{
	x = in_x;
	y = in_y;
}

Location Location::operator+( const Location& loc ) const
{
	return Location(x + loc.x, y + loc.y);
}

Location& Location::operator+=( const Location& loc )
{
	return *this = *this + loc;
}

Location Location::operator-( const Location& loc ) const
{
	return Location( x - loc.x, y - loc.y );
}

Location& Location::operator-=( const Location& loc )
{
	return *this = *this - loc;
}

Location Location::operator*( int val ) const
{
	return Location( x * val, y * val );
}

Location& Location::operator*=( int val )
{
	return *this = *this * val;
}

Location Location::operator/( int val ) const
{
	return Location( x / val, y / val );
}

Location& Location::operator/=( int val )
{
	return *this = *this / val;
}
