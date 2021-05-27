#include "Pawn.h"
#include "Cell.h"
#include <cassert>

Pawn::Pawn( const Cell& cell, bool in_isLightSide )
	:
	Piece( cell, in_isLightSide )
{
}

void Pawn::Move( Cell& cur_pos, Cell& nxt_pos )
{
}

bool Pawn::IsForwardMove( const Location& move_vec ) const
{
	if( isLightSide )
	{
		return move_vec.x < 0;
	}
	return move_vec.x > 0;
}

bool Pawn::IsFastForwardMove( const Board& brd, const Location& move_vec, const Cell& nxt_pos ) const
{
	assert( IsForwardMove( move_vec ) && PathIsFree( brd, move_vec, nxt_pos ) );
	return  (std::abs( move_vec.x ) == 2) && (std::abs( move_vec.y ) == 0);
}

bool Pawn::IsStepForwardMove( const Location& move_vec, const Cell& nxt_pos ) const
{
	assert( IsForwardMove(move_vec) && nxt_pos.IsFree() );
	return (std::abs( move_vec.x ) == 1) && (std::abs( move_vec.y ) == 0);;
}
