#include "King.h"
#include "Board.h"

King::King( class CellArray::Cell& cell, bool in_isLightSide )
	:
	Piece( cell, in_isLightSide )
{
}

void King::Move( class Board& brd )
{
	const bool currentTurn = brd.GetCurrentTurn();
	CellArray::Cell& next_cell = brd.GetNextCell();
	const Location& cur_pos = brd.GetIdx( brd.GetCurrentCell().location );
	const Location& nxt_pos = brd.GetIdx( brd.GetNextCell().location );
	const Location& move_vec = Board::GetMoveVec( cur_pos, nxt_pos );

	if( brd.IsOneCellRange(move_vec) )
	{
		if( next_cell.IsFree() || brd.NextIsEnemy() )
		{
			cell->MovePieceTo( next_cell );
			cell = &next_cell;
			brd.SetNextSideMove();
		}
	}

	brd.DeselectLastCell();

	const bool nextTurn = currentTurn != brd.GetCurrentTurn();
	if( nextTurn )
	{
		isMoved = true;
		brd.DeselectAllCells();
	}
}
