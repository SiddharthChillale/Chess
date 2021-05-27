#pragma once

class Location
{
public:
	Location() = default;
	Location( int in_x, int in_y );
	bool operator==( const Location& rhs ) const;
	bool operator!=( const Location& rhs ) const;
	Location operator+( const Location& rhs ) const;
	Location& operator+=( const Location& rhs );
	Location operator-( const Location& rhs ) const;
	Location& operator-=( const Location& rhs );
	Location operator*( int rhs ) const;
	Location& operator*=( int rhs );
	Location operator/( int rhs ) const;
	Location& operator/=( int rhs );
public:
	int x;
	int y;
};