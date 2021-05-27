#include "Board.h"
#include <cassert>

Board::Board()
{
	for( int i = 0; i < dimension; i++ )
	{
		for( int j = 0; j < dimension; j++ )
		{
			cells.emplace_back( loc, i, j );
		}
	}
}

Location Board::GetLocation() const
{
	return loc;
}

void Board::Draw( Graphics& gfx ) const
{
	size_t size = cells.size();
	for( size_t i = 0; i < size; i++ )
	{
		cells[i].Draw( gfx, idxCurrentCell == i || idxTargetCell == i );
	}
}

bool Board::MouseIsOnBoard( const Graphics& gfx, const Mouse& mouse ) const
{
	const int mouse_X = mouse.GetPosX();
	const int mouse_Y = mouse.GetPosY();
	return mouse_X >= loc.x && mouse_X < (gfx.ScreenWidth - loc.x) &&
		mouse_Y >= loc.y && mouse_Y < (gfx.ScreenHeight - loc.y);
}

int Board::GetCell_idx( const Location& in_loc ) const
{
	const Location locRelativeToBoard = in_loc - loc;
	const Location cell_Idx = locRelativeToBoard / Cell::GetDimension();
	int idx = cell_Idx.x * dimension + cell_Idx.y;
	assert( idx >= 0 && idx < cells.size() );
	return idx;
}

void Board::PorcessInput( const Graphics& gfx, const Mouse& mouse )
{
	if( isReleasedLeft && mouse.LeftIsPressed() && MouseIsOnBoard( gfx, mouse ) )
	{
		isReleasedLeft = false;
		const Location mouse_loc( mouse.GetPosX(), mouse.GetPosY() );
		const int idx = GetCell_idx( mouse_loc );
		if( !idxCurrentCell )
		{
			idxCurrentCell = idx;
		}
		else if( idxCurrentCell == idx )
		{
			idxCurrentCell = {};
			idxTargetCell = {};
		}
		else if( !idxTargetCell )
		{
			idxTargetCell = idx;
		}
	}
	if( !mouse.LeftIsPressed() )
	{
		isReleasedLeft = true;
	}
}
