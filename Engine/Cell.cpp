#include "Cell.h"
#include "Board.h"
#include <cassert>

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
	if( piece )
	{
		piece->Draw( gfx );
	}
}

int Cell::GetDimension()
{
	return dimension;
}

Location Cell::GetLocation() const
{
	return loc;
}

bool Cell::IsFree() const
{
	return bool(!piece);
}

bool Cell::PieceSide() const
{
	assert( piece );
	return piece->PieceSide();
}

void Cell::PutPiece( std::unique_ptr<Piece> in_piece )
{
	assert( !piece );
	piece = std::move( in_piece );
}

void Cell::RemovePiece()
{
	assert( piece );
	piece.release();
}

void Cell::MovePieceTo( Cell& nxt_pos )
{
	assert( piece );
	if( nxt_pos.piece )
	{
		nxt_pos.RemovePiece();
	}
	nxt_pos.piece = std::move( piece );
}
