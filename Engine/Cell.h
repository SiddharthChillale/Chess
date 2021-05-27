#pragma once

#include "Graphics.h"
#include "Location.h"

class Cell
{
public:
	Cell( const Location& brd_loc, int x, int y );
	void Draw( Graphics& gfx, bool isSelected = false ) const;
private:
	const Location loc;
	const Color c;
	static constexpr int dimension = 75;
	static constexpr int offset = 1;
	static constexpr Color lightColor = Color( 238, 238, 210 );
	static constexpr Color darkColor = Color( 118, 150, 86 );
	static constexpr Color selectedColor = Color(0,0,255);
};