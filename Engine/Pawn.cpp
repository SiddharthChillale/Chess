#include "Pawn.h"
#include "Cell.h"
#include "Board.h"
#include <cassert>

Pawn::Pawn( Cell& cell, bool in_isLightSide )
	:
	Piece( cell, in_isLightSide )
{
}

void Pawn::Move( Board& brd, const Location& move_vec, Cell& nxt_pos )
{
	const bool currentTurn = brd.GetCurrentTurn();
	
	const Location cur_loc = brd.PixelToCellDim(cell->GetLocation());
	Cell& cur_pos = brd.GetCell( cur_loc.x, cur_loc.y );

	if( IsForwardMove( move_vec ) )
	{
		if( nxt_pos.IsFree() )
		{
			if( IsStepForwardMove( move_vec, nxt_pos ) )
			{
				// do step forward move

				cell->MovePieceTo( nxt_pos );
				cell = &nxt_pos;
				brd.SetNextSideMove();
				isMoved = true;
			}
			else if( IsFastForwardMove( move_vec, nxt_pos ) && PathIsFree( brd, move_vec, nxt_pos ) )
			{
				// do fast forward move

				isEnPasant = true;
				cell->MovePieceTo( nxt_pos );
				cell = &nxt_pos;
				brd.SetNextSideMove();

			}
			else if( IsDiagonal(move_vec) )
			{
				const Location target = GetEnPasantTarget( move_vec );
				if( TargetIsEnPasant(brd,target) )
				{
					// attack enPasant
					Cell& enPasant = GetEnPasant( brd, move_vec );
					cell->MovePieceTo( nxt_pos );
					cell = &nxt_pos;
					enPasant.RemovePiece();
					brd.SetNextSideMove();
				}
			}
		}
		else if( IsDiagonal( move_vec ) && IsOneCellRange( move_vec ) )
		{
			if( IsEnemyCell( nxt_pos ) )
			{
				// attack directly
				cell->MovePieceTo( nxt_pos );
				cell = &nxt_pos;
				brd.SetNextSideMove();
			}
		}
	}
	else
	{
		brd.DeselectTargetCell();
	}
	if( currentTurn != brd.GetCurrentTurn() && (isEnPasant == true) )
	{
		nxt_pos.turnOffEnPassant();
		brd.DeselectBothCells();
	}
}

bool Pawn::IsForwardMove( const Location& move_vec ) const
{
	if( isLightSide )
	{
		return move_vec.y > 0;
	}
	return move_vec.y < 0;
}

bool Pawn::IsFastForwardMove( const Location& move_vec, const Cell& nxt_pos ) const
{
	assert( IsForwardMove( move_vec ) && nxt_pos.IsFree() );
	return  (std::abs( move_vec.y ) == 2) && (std::abs( move_vec.x ) == 0);
}

bool Pawn::IsStepForwardMove( const Location& move_vec, const Cell& nxt_pos ) const
{
	assert( IsForwardMove(move_vec) && nxt_pos.IsFree() );
	return (std::abs( move_vec.x ) == 0) && (std::abs( move_vec.y ) == 1);
}

Location Pawn::GetEnPasantTarget( const Location& move_vec ) const
{
	const Location target = cell->GetLocation() + Location( move_vec.x * 0, move_vec.y );
	return target;
}

Cell& Pawn::GetEnPasant( Board& brd, const Location& move_vec )
{
	assert( TargetIsEnPasant( brd, move_vec ) );
	return brd.GetCell( move_vec.x, move_vec.y );
}

bool Pawn::TargetIsEnPasant( const Board& brd, const Location& target ) const
{
	const Cell& MaybeEnPasant = brd.GetConstCell( brd.PixelToCellDim( target ) );
	if( !MaybeEnPasant.IsFree() &&
		(PieceSide() != MaybeEnPasant.PieceSide()) &&
		MaybeEnPasant.IsEnPasant() )
	{
		return true;
	}
	return false;
}
