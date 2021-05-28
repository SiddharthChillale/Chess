#include "Knight.h"

#include "Board.h"

Knight::Knight( Cell& cell, bool in_isLightSide )
	:
	Piece( cell, in_isLightSide )
{
}

void Knight::Move( Board& brd, const Location& move_vec, Cell& nxt_pos )
{
	const bool currentTurn = brd.GetCurrentTurn();

	const Location cur_loc = brd.PixelToCellDim( cell->GetLocation() );
	Cell& cur_pos = brd.GetCell( cur_loc.x, cur_loc.y );

	if( IsKnightMove( move_vec ) )
	{
		if( nxt_pos.IsFree() || IsEnemyCell( nxt_pos ) )
		{
			cell->MovePieceTo( nxt_pos );
			cell = &nxt_pos;
			brd.SetNextSideMove();
		}
	}

	brd.DeselectTargetCell();

	const bool nextTurn = currentTurn != brd.GetCurrentTurn();
	if( nextTurn )
	{
		isMoved = true;
		brd.DeselectBothCells();
	}
}

bool Knight::IsKnightMove( const Location& move_vec ) const
{
	return std::abs(move_vec.x) + std::abs(move_vec.y) == 3;
}
