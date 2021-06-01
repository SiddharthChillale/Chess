#include "Pawn.h"
#include "CellArray.h"
#include "Board.h"
#include <cassert>

Pawn::Pawn( Cell& cell, bool in_isLightSide )
	:
	Piece( cell, in_isLightSide )
{
}

void Pawn::Move( Board& brd )
{
	const bool currentTurn = brd.GetCurrentTurn();
	Cell& next_cell = brd.GetNextCell();
	const Location& cur_pos = brd.GetIdx( brd.GetCurrentCell().location );
	const Location& nxt_pos = brd.GetIdx( brd.GetNextCell().location );
	const Location& move_vec = Board::GetMoveVec( cur_pos, nxt_pos );

	if( brd.IsForwardMove( move_vec ) )
	{
		if( next_cell.IsFree() )
		{
			if( brd.IsStepForwardMove( move_vec ) )
			{
				// Do step forward move
				cell->MovePieceTo( next_cell );
				cell = &next_cell;
				brd.SetNextSideMove();
			}
			else if( brd.IsFastForwardMove( move_vec ) && brd.PathIsFree( move_vec ) )
			{
				// Do fast forward move
				isEnPasant = true;
				cell->MovePieceTo( next_cell );
				cell = &next_cell;
				brd.SetNextSideMove();
			}
			else if( brd.IsDiagonal(move_vec) )
			{
				const Location target = brd.GetEnPasantTarget( move_vec );
				if( brd.TargetIsEnPasant( target ) )
				{
					// Attack enPasant
					Cell& enPasant = brd.GetCell( target );
					cell->MovePieceTo( next_cell );
					cell = &next_cell;
					enPasant.RemovePiece();
					brd.SetNextSideMove();
				}
			}
		}
		else if( brd.IsDiagonal( move_vec ) && brd.IsOneCellRange( move_vec ) )
		{
			if( brd.NextIsEnemy() )
			{
				// Attack directly
				cell->MovePieceTo( next_cell );
				cell = &next_cell;
				brd.SetNextSideMove();
			}
		}
	}

	brd.DeselectLastCell();

	const bool nextTurn = currentTurn != brd.GetCurrentTurn();
	if( nextTurn && (isEnPasant && isMoved) )
	{
		next_cell.turnOffEnPassant();
	}
	if( nextTurn )
	{
		isMoved = true;
		brd.DeselectAllCells();
	}
}