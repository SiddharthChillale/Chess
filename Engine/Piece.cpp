#include "Piece.h"
#include "Cell.h"

Piece::Piece( const Cell& cell, bool in_isLightSide )
	:
	cell_loc_ptr( cell.GetLocationPtr() ),
	isLightSide( in_isLightSide ),
	c( in_isLightSide ? lightSideColor : darkSideColor )
{
	
}

void Piece::Draw( Graphics& gfx) const
{
	const int center = Cell::GetDimension() / 2;
	const Location global_location = *cell_loc_ptr + Location( center, center );
	gfx.DrawCircle( global_location.x, global_location.y, 25, c );
}
