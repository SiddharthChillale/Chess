#include "Piece.h"
#include "CellArray.h"
#include "Board.h"
#include <cassert>

Piece::Piece( CellArray::Cell& in_cell, bool in_isLightSide )
	:
	cell( &in_cell ), 
	isLightSide( in_isLightSide ),
	c( in_isLightSide ? lightSideColor : darkSideColor )
{
	
}

void Piece::Draw( Graphics& gfx) const
{
	const int center = CellArray::Cell::dimension / 2;
	const Location global_location = cell->location + Location( center, center );
	gfx.DrawCircle( global_location.x, global_location.y, 25, c );
}

bool Piece::PieceSide() const
{
	return isLightSide;
}

Location Piece::GetMoveVec( const CellArray::Cell& cur_pos, const CellArray::Cell& nxt_pos )
{
	const Location current = cur_pos.location;
	const Location next = nxt_pos.location;
	const Location move_vec = (next - current) / CellArray::Cell::dimension;
	return move_vec;
}

void Piece::RecordDeath()
{
	isAlive = false;
}

void Piece::TurnOffEnPasant()
{
	isEnPasant = false;
}

Location Piece::GetNormalizedMove( const Location& move_vec )
{
	Location result(0,0);
	assert( move_vec != result );

	if( move_vec.x != 0 )
	{
		return move_vec / abs( move_vec.x );
	}
	return move_vec / abs( move_vec.y );
}

bool Piece::IsOneCellRange( const Location& move_vec ) const
{
	const int abs_x = abs( move_vec.x );
	const int abs_y = abs( move_vec.y );
	return (abs_x < 2) && (abs_y < 2);
}

bool Piece::IsDiagonal( const Location& move_vec ) const
{
	return abs(move_vec.x) == abs(move_vec.y);
}

bool Piece::IsHorizontal( const Location& move_vec ) const
{
	return move_vec.y == 0;
}

bool Piece::IsVertical( const Location& move_vec ) const
{
	return move_vec.x == 0;
}

bool Piece::PathIsFree( const Board& brd, const Location& move_vec, const CellArray::Cell& nxt_pos ) const
{
	const Location& norm_move_vec = Piece::GetNormalizedMove( move_vec );
	const Location destination = brd.PixelToCellDim( nxt_pos.GetLocation() );
	const Location current = brd.PixelToCellDim( cell->GetLocation() );
	Location cur_pos = current + norm_move_vec;
	while( cur_pos != destination )
	{
		const bool isNotFree = !brd.GetConstCell( cur_pos ).IsFree();
		if( isNotFree )
		{
			return false;
		}
		cur_pos += norm_move_vec;
	}
	return true;
}

bool Piece::IsFreeCell( const CellArray::Cell& nxt_pos ) const
{
	return nxt_pos.IsFree();
}

bool Piece::IsEnemyCell( const CellArray::Cell& nxt_pos ) const
{
	if( nxt_pos.IsFree() )
	{
		return false;
	}
	return PieceSide() != nxt_pos.PieceSide();
}

bool Piece::IsEnPasant() const
{
	return isEnPasant;
}

bool Piece::IsAlive() const
{
	return isAlive;
}
