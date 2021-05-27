#pragma once

class Location
{
public:
	Location() = default;
	Location( int in_x, int in_y );
	Location operator+( const Location& loc ) const;
	Location& operator+=( const Location& loc );
	Location operator-( const Location& loc ) const;
	Location& operator-=( const Location& loc );
	Location operator*( int val ) const;
	Location& operator*=( int val );
public:
	int x;
	int y;
};