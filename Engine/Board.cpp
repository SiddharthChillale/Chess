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
