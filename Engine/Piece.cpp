#include "Piece.h"
#include "Cell.h"
#include "Board.h"
#include <cassert>

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

bool Piece::PieceSide() const
{
	return isLightSide;
}

bool Piece::IsEnemy( const Cell& nxt_pos ) const
{
	return isLightSide != nxt_pos.PieceSide();
}

Location Piece::GetMoveVec( const Cell& cur_pos, const Cell& nxt_pos )
{
	return nxt_pos.GetLocation() - cur_pos.GetLocation();
}

Location Piece::GetNormalizedMove( const Location& move_vec )
{
	assert( move_vec != Location() );
	if( move_vec.x != 0 )
	{
		return Location( move_vec / std::abs(move_vec.x) );
	}
	return Location( move_vec / std::abs( move_vec.y ) );
}

bool Piece::IsDiagonal( const Location& move_vec ) const
{
	return std::abs(move_vec.x) == 1 && std::abs(move_vec.y) == 1;
}

bool Piece::IsHorizontal( const Location& move_vec ) const
{
	return move_vec.x == 0;
}

bool Piece::IsVertical( const Location& move_vec ) const
{
	return move_vec.y == 0;
}

bool Piece::IsLongPath( const Location& move_vec, const Cell& nxt_pos ) const
{
	assert( IsHorizontal( move_vec ) || IsVertical( move_vec ) || IsDiagonal( move_vec ) );
	return std::abs( move_vec.x ) > 1 || std::abs( move_vec.y ) > 1;
}

bool Piece::PathIsFree( const Board& brd, const Location& move_vec, const Cell& nxt_pos ) const
{
	assert( IsLongPath( move_vec, nxt_pos ) );
	const Location& norm_move_vec = Piece::GetNormalizedMove( move_vec );
	const Location destination = nxt_pos.GetLocation();
	Location cur_pos = cell->GetLocation() + norm_move_vec;
	while( cur_pos != destination )
	{
		const bool isNotFree = !brd.GetConstCell( cur_pos.x, cur_pos.y ).IsFree();
		if( isNotFree )
		{
			return false;
		}
		cur_pos += norm_move_vec;
	}
	return true;
}

bool Piece::IsFreeCell( const Cell& nxt_pos ) const
{
	return nxt_pos.IsFree();
}

bool Piece::IsEnemyCell( const Cell& nxt_pos ) const
{
	assert( !IsFreeCell( nxt_pos ) );
	return isLightSide != nxt_pos.PieceSide();
}
