#include "Board.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Rook.h"
#include "Knight.h"
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

	PutPawns();
	PutBishops();
	PutRooks();
	PutKnights();
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

const Cell& Board::GetConstCell( const Location& cell_dim ) const
{
	return cells[cell_dim.x * dimension + cell_dim.y];
}

Location Board::PixelToCellDim( const Location& piexel_dim ) const
{
	const Location locRelativeToBoard = piexel_dim - loc;
	return locRelativeToBoard / Cell::GetDimension();
}

Cell& Board::GetCell( int cell_dim1, int cell_dim2 )
{
	return cells[cell_dim1 * dimension + cell_dim2];
}

void Board::SetNextSideMove()
{
	isLightSideMove = !isLightSideMove;
}

bool Board::GetCurrentTurn() const
{
	return isLightSideMove;
}

void Board::DeselectTargetCell()
{
	idxTargetCell = {};
}

void Board::DeselectBothCells()
{
	idxCurrentCell = {};
	idxTargetCell = {};
}

void Board::PutKnights()
{
	const bool isLightSide = true;
	const bool isDarkSide = !isLightSide;
	const int light_pawn_y = dimension - 1;
	const int dark_pawn_y = 0;

	for( int x = 1; x < dimension; x += 5 )
	{
		Cell& c_light = GetCell( x, light_pawn_y );
		c_light.PutPiece( std::make_unique<Knight>( c_light, isLightSide ) );
		Cell& c_dark = GetCell( x, dark_pawn_y );
		c_dark.PutPiece( std::make_unique<Knight>( c_dark, isDarkSide ) );
	}
}

void Board::PutBishops()
{
	const bool isLightSide = true;
	const bool isDarkSide = !isLightSide;
	const int light_pawn_y = dimension - 1;
	const int dark_pawn_y = 0;

	for( int x = 2; x < dimension; x += 3 )
	{
		Cell& c_light = GetCell( x, light_pawn_y );
		c_light.PutPiece( std::make_unique<Bishop>( c_light, isLightSide ) );
		Cell& c_dark = GetCell( x, dark_pawn_y );
		c_dark.PutPiece( std::make_unique<Bishop>( c_dark, isDarkSide ) );
	}
}

void Board::PutRooks()
{
	const bool isLightSide = true;
	const bool isDarkSide = !isLightSide;
	const int light_pawn_y = dimension - 1;
	const int dark_pawn_y = 0;

	for( int x = 0; x < dimension; x += dimension - 1 )
	{
		Cell& c_light = GetCell( x, light_pawn_y );
		c_light.PutPiece( std::make_unique<Rook>( c_light, isLightSide ) );
		Cell& c_dark = GetCell( x, dark_pawn_y );
		c_dark.PutPiece( std::make_unique<Rook>( c_dark, isDarkSide ) );
	}
}

void Board::PutPawns()
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

int Board::GetCell_idx( const Location& pixel_dim ) const
{
	const Location cell_Idx = PixelToCellDim( pixel_dim );
	int idx = cell_Idx.x * dimension + cell_Idx.y;
	assert( idx >= 0 && idx < cells.size() );
	return idx;
}

void Board::ProcessInput( const Graphics& gfx, const Mouse& mouse )
{
	if( isReleasedLeft && mouse.LeftIsPressed() && MouseIsOnBoard( gfx, mouse ) )
	{
		isReleasedLeft = false;
		const Location mouse_loc = Location( mouse.GetPosX(), mouse.GetPosY() );
		const int idx = GetCell_idx( mouse_loc );
		if( !idxCurrentCell )
		{
			if( !cells[idx].IsFree() && (cells[idx].PieceSide() == isLightSideMove) )
			{
				idxCurrentCell = idx;
			}
		}
		else if( idxCurrentCell == idx )
		{
			DeselectBothCells();
		}
		else if( !idxTargetCell )
		{
			idxTargetCell = idx;
			Cell& cur_pos = cells[idxCurrentCell.value()];
			Cell& nxt_pos = cells[idxTargetCell.value()];
			cur_pos.PerformMovement( *this, nxt_pos );
		}
	}
	if( !mouse.LeftIsPressed() )
	{
		isReleasedLeft = true;
	}
}
