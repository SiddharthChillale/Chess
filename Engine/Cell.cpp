#include "Cell.h"
#include "Board.h"

Cell::Cell( const Location& brd_loc, int x, int y )
	:
	loc( brd_loc + Location( x, y ) * dimension ),
	c( ((x + y) % 2) ? darkColor : lightColor )
{
}

void Cell::Draw( Graphics& gfx, bool isSelected ) const
{
	Color col = isSelected ? selectedColor : c;
	gfx.DrawRect( loc.x + offset, loc.y + offset, loc.x + dimension - offset, loc.y + dimension - offset, col );
}
