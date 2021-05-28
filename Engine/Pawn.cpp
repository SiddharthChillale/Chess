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
				// Do step forward move
				cell->MovePieceTo( nxt_pos );
				cell = &nxt_pos;
				brd.SetNextSideMove();
			}
			else if( IsFastForwardMove( move_vec, nxt_pos ) && PathIsFree( brd, move_vec, nxt_pos ) )
			{
				// Do fast forward move
				isEnPasant = true;
				cell->MovePieceTo( nxt_pos );
				cell = &nxt_pos;
				brd.SetNextSideMove();
			}
			else if( IsDiagonal(move_vec) )
			{
				const Location target = GetEnPasantTarget( brd, move_vec );
				if( TargetIsEnPasant( brd, target ) )
				{
					// Attack enPasant
					Cell& enPasant = GetEnPasant( brd, target );
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
				// Attack directly
				cell->MovePieceTo( nxt_pos );
				cell = &nxt_pos;
				brd.SetNextSideMove();
			}
		}
	}

	brd.DeselectTargetCell();

	const bool nextTurn = currentTurn != brd.GetCurrentTurn();
	if( nextTurn && (isEnPasant && isMoved) )
	{
		nxt_pos.turnOffEnPassant();
	}
	if( nextTurn )
	{
		isMoved = true;
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
	return  (std::abs( move_vec.y ) == 2) && (std::abs( move_vec.x ) == 0) && (!isMoved);
}

bool Pawn::IsStepForwardMove( const Location& move_vec, const Cell& nxt_pos ) const
{
	assert( IsForwardMove(move_vec) && nxt_pos.IsFree() );
	return (std::abs( move_vec.x ) == 0) && (std::abs( move_vec.y ) == 1);
}

Location Pawn::GetEnPasantTarget( const Board& brd, const Location& move_vec ) const
{
	const Location target = brd.PixelToCellDim( cell->GetLocation() ) - Location( move_vec.x, move_vec.y * 0 );
	return target;
}

Cell& Pawn::GetEnPasant( Board& brd, const Location& move_vec )
{
	assert( TargetIsEnPasant( brd, move_vec ) );
	return brd.GetCell( move_vec.x, move_vec.y );
}

bool Pawn::TargetIsEnPasant( const Board& brd, const Location& target ) const
{
	const Cell& MaybeEnPasant = brd.GetConstCell( target );
	if( !MaybeEnPasant.IsFree() &&
		(PieceSide() != MaybeEnPasant.PieceSide()) && MaybeEnPasant.IsEnPasant() )
	{
		return true;
	}
	return false;
}
