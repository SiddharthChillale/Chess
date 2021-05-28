#pragma once

class Location
{
public:
	Location( int in_x = 0, int in_y = 0 );
	Location& operator=( const Location& loc ) = default;
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