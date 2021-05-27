#include "Piece.h"
#include "Cell.h"

Piece::Piece( const Cell& in_cell, bool in_isLightSide )
	:
	cell( &in_cell ), 
	isLightSide( in_isLightSide ),
	c( in_isLightSide ? lightSideColor : darkSideColor )
{
	
}

void Piece::Draw( Graphics& gfx) const
{
	const int center = Cell::GetDimension() / 2;
	const Location global_location = cell->GetLocation() + Location( center, center );
	gfx.DrawCircle( global_location.x, global_location.y, 25, c );
}
