#include "Board.h"
#include <cassert>

Cell::Cell( const Location& in_loc, int row_idx, int col_idx, Color in_c )
	:
	location( in_loc ),
	color( in_c )
{
}

void Cell::Draw( Graphics& gfx, Color in_c ) const
{
	const int top_left_x = location.x + offset;
	const int top_left_y = location.y + offset;
	const int bottom_right_x = location.x + dimension - offset;
	const int bottom_right_y = location.y + dimension - offset;
	gfx.DrawRect( top_left_x, top_left_y, bottom_right_x, bottom_right_y, in_c );
	if( piece )
	{
		piece->Draw( gfx );
	}
}

void Cell::Draw( Graphics& gfx ) const
{
	Draw( gfx, color );
	if( piece )
	{
		piece->Draw( gfx );
	}
}

void Cell::PutPiece( std::shared_ptr<Piece> in_piece )
{
	assert( !piece );
	piece = in_piece;
	piece->OccupyCell( this );
}

void Cell::RemovePiece()
{
	assert( piece );
	piece->OccupyCell( nullptr );
	piece.reset();
}

void Cell::MovePieceTo( Cell& nxt_pos )
{
	piece->RecordMove();
	assert( piece );
	if( nxt_pos.piece )
	{
		nxt_pos.RemovePiece();
	}
	nxt_pos.PutPiece( piece );
	piece.reset();
}

void Cell::PerformMovement( Board& brd )
{
	brd.GetCurrentCell().piece->Move( brd );
}

bool Cell::IsFree() const
{
	return !piece;
}

bool Cell::PieceSide() const
{
	assert( piece );
	return piece->PieceSide();
}

bool Cell::IsEnPasant() const
{
	return piece->IsEnPasant();
}

bool Cell::IsAlive() const
{
	assert( piece );
	return piece->IsAlive();
}

void Cell::turnOffEnPassant()
{
	piece->TurnOffEnPasant();
}