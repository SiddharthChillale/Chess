#include "Queen.h"
#include "Board.h"

Queen::Queen( Cell& cell, bool in_isLightSide )
	:
	Piece( cell, in_isLightSide )
{
}

void Queen::Move( Board& brd, const Location& move_vec, Cell& nxt_pos )
{
	const bool currentTurn = brd.GetCurrentTurn();

	const Location cur_loc = brd.PixelToCellDim( cell->GetLocation() );
	Cell& cur_pos = brd.GetCell( cur_loc.x, cur_loc.y );

	if( IsDiagonal( move_vec ) || IsHorizontal( move_vec ) || IsVertical( move_vec ) )
	{
		if( PathIsFree( brd, move_vec, nxt_pos ) )
		{
			if( nxt_pos.IsFree() || IsEnemyCell( nxt_pos ) )
			{
				cell->MovePieceTo( nxt_pos );
				cell = &nxt_pos;
				brd.SetNextSideMove();
			}
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