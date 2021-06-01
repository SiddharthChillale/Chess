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