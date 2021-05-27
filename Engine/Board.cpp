#include "Board.h"
#include "Pawn.h"
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

	PutPiecesInCells();
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

const Cell& Board::GetConstCell( int cell_dim1, int cell_dim2 ) const
{
	return cells[cell_dim1 * dimension + cell_dim2];
}

Cell& Board::GetCell( int cell_dim1, int cell_dim2 )
{
	return cells[cell_dim1 * dimension + cell_dim2];
}

void Board::SetNextSideMove()
{
	isLightSideMove = !isLightSideMove;
}

void Board::PutPiecesInCells()
{
	const bool isLightSide = true;
	const bool isDarkSide = !isLightSide;

	const int light_pawn_y = dimension - 2;
	const int dark_pawn_y = 1;
	for( int i = 0; i < dimension; i++ )
	{
		Cell& c_light = GetCell( i, light_pawn_y );
		c_light.PutPiece( std::make_unique<Pawn>( c_light, isLightSide ) );

		Cell& c_dark = GetCell( i, dark_pawn_y );
		c_dark.PutPiece( std::make_unique<Pawn>( c_dark, isDarkSide ) );
	}
}

int Board::GetCell_idx( const Mouse& mouse ) const
{
	const Location mouse_loc = Location( mouse.GetPosX(), mouse.GetPosY() );
	const Location locRelativeToBoard = mouse_loc - loc;
	const Location cell_Idx = locRelativeToBoard / Cell::GetDimension();
	int idx = cell_Idx.x * dimension + cell_Idx.y;
	assert( idx >= 0 && idx < cells.size() );
	return idx;
}

void Board::ProcessInput( const Graphics& gfx, const Mouse& mouse )
{
	if( isReleasedLeft && mouse.LeftIsPressed() && MouseIsOnBoard( gfx, mouse ) )
	{
		isReleasedLeft = false;
		const int idx = GetCell_idx( mouse );
		if( !idxCurrentCell )
		{
			if( !cells[idx].IsFree() && (cells[idx].PieceSide() == isLightSideMove) )
			{
				idxCurrentCell = idx;
			}
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
