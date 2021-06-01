#include "Board.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Rook.h"
#include "Knight.h"
#include "King.h"
#include "Queen.h"
#include <cassert>

Board::Board( const Location& loc, int dimenstion )
	:
	arr( loc, dimenstion )
{
}

void Board::Draw( Graphics& gfx ) const
{
	arr.Draw( gfx );
}

void Board::SetNextSideMove()
{
	isLightSideMove = !isLightSideMove;
}

void Board::PerformMovement()
{
	const Location move_vec = GetMoveVec( GetCurrentCell().location, GetNextCell().location );
	GetCurrentCell().piece->Move( *this );
}

bool Board::GetCurrentTurn() const
{
	return isLightSideMove;
}

void Board::ProcessInput( const Graphics& gfx, const Mouse& mouse )
{
	if( isReleasedLeft && mouse.LeftIsPressed() && arr.MouseIsOnArray( mouse ) )
	{
		isReleasedLeft = false;
		const Location mouse_loc_idx = Location( mouse.GetPosX(), mouse.GetPosY() );
		CellArray::Cell& cell_to_select = arr[mouse_loc_idx];
		if( arr.selectedCellsCount() == 0 )
		{
			if( !cell_to_select.IsFree() && (cell_to_select.PieceSide() == isLightSideMove) )
			{
				arr.Select( cell_to_select );
			}
		}
		else if( arr.IsSelected( cell_to_select ) )
		{
			arr.DeselectAll();
		}
		else if( arr.selectedCellsCount() == 1 )
		{
			arr.Select( cell_to_select );
			CellArray::Cell::PerformMovement( arr.GetSelected(0), arr.GetSelected(1) );
		}
	}
	if( !mouse.LeftIsPressed() )
	{
		isReleasedLeft = true;
	}
}

bool Board::PathIsFree( const Location& move_vec ) const
{
	const Location& norm_move_vec = Board::GetNormalizedMove( move_vec );
	const Location destination = arr.GetIdx( GetCurrentCell().location );
	const Location current = arr.GetIdx( GetNextCell().location );
	Location cur_pos = current + norm_move_vec;
	while( cur_pos != destination )
	{
		const bool isNotFree = !GetCurrentCell().IsFree();
		if( isNotFree )
		{
			return false;
		}
		cur_pos += norm_move_vec;
	}
	return true;
}

CellArray::Cell& Board::GetCurrentCell()
{
	return arr.GetSelected( 0 );
}

CellArray::Cell& Board::GetNextCell()
{
	return arr.GetSelected( 1 );
}

const CellArray::Cell& Board::GetCurrentCell() const
{
	return arr.GetSelected( 0 );
}

const CellArray::Cell& Board::GetNextCell() const
{
	return arr.GetSelected( 1 );
}

void Board::DeselectLastCell()
{
	arr.DeselectLast();
}

void Board::DeselectAllCells()
{
	arr.DeselectAll();
}

Location Board::GetIdx( const Location& loc ) const
{
	return arr.GetIdx( loc );
}

CellArray::Cell& Board::GetCell( const Location& locIdx )
{
	return arr[locIdx];
}

const CellArray::Cell& Board::GetCell( const Location& locIdx ) const
{
	return arr[locIdx];
}

Location Board::GetMoveVec( const Location& current, const Location& next )
{
	const Location move_vec = (next - current) / CellArray::Cell::dimension;
	return move_vec;
}

Location Board::GetNormalizedMove( const Location& move_vec )
{
	Location result( 0, 0 );
	assert( move_vec != result );

	if( move_vec.x != 0 )
	{
		return move_vec / abs( move_vec.x );
	}
	return move_vec / abs( move_vec.y );
}

bool Board::IsOneCellRange( const Location& move_vec ) const
{
	const int abs_x = abs( move_vec.x );
	const int abs_y = abs( move_vec.y );
	return (abs_x < 2) && (abs_y < 2);
}

bool Board::IsDiagonal( const Location& move_vec ) const
{
	return abs( move_vec.x ) == abs( move_vec.y );
}

bool Board::IsHorizontal( const Location& move_vec ) const
{
	return move_vec.y == 0;
}

bool Board::IsVertical( const Location& move_vec ) const
{
	return move_vec.x == 0;
}

bool Board::NextIsFree() const
{
	return GetNextCell().IsFree();
}

bool Board::NextIsEnemy() const
{
	if( GetNextCell().IsFree() )
	{
		return false;
	}
	return GetCurrentCell().PieceSide() != GetNextCell().PieceSide();
}

bool Board::IsForwardMove( const Location& move_vec ) const
{
	if( GetCurrentCell().piece->IsLightSide() )
	{
		return move_vec.y < 0;
	}
	return move_vec.y > 0;
}

bool Board::IsFastForwardMove( const Location& move_vec ) const
{
	assert( IsForwardMove( move_vec ) && GetNextCell().IsFree() );
	return  (std::abs( move_vec.y ) == 2) && (std::abs( move_vec.x ) == 0) && (!GetCurrentCell().piece->IsMoved());
}

bool Board::IsStepForwardMove( const Location& move_vec ) const
{
	assert( IsForwardMove( move_vec ) && GetNextCell().IsFree() );
	return (std::abs( move_vec.x ) == 0) && (std::abs( move_vec.y ) == 1);
}

Location Board::GetEnPasantTarget( const Location& move_vec ) const
{
	const Location target = GetIdx( GetCurrentCell().location ) + Location( move_vec.x, move_vec.y * 0 );
	return target;
}

bool Board::TargetIsEnPasant( const Location& target ) const
{
	const CellArray::Cell& MaybeEnPasant = GetCell( target );
	if( !MaybeEnPasant.IsFree() &&
		(GetCurrentCell().piece->PieceSide() != MaybeEnPasant.PieceSide()) && MaybeEnPasant.IsEnPasant() )
	{
		return true;
	}
	return false;
}
