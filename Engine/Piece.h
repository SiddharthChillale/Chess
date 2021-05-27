#pragma once

#include "Graphics.h"
#include "Location.h"

class Piece
{
public:
	Piece( const class Cell& cell, bool in_isLightSide);
	void Draw( Graphics& gfx) const;
protected:
	const Location* cell_loc_ptr;
	const bool isLightSide;
	const Color c;
	static constexpr Color lightSideColor = Color( 186, 202, 68 );
	static constexpr Color darkSideColor = Color( 101, 67, 33 );
};