#include "CellArray.h"
#include <cassert>

CellArray::Cell::Cell( const Location& in_loc, int row_idx, int col_idx, Color in_c )
	:
	loc( in_loc + Location( row_idx, col_idx ) * dimension ),
	c( in_c )
{
}

CellArray:: Cell::Cell( const Location& in_loc, int row_idx, int col_idx )
	:
	loc( in_loc + Location( row_idx, col_idx ) * dimension ),
	c( ((row_idx + col_idx) % 2) ? CellArray::darkCell : CellArray::lightCell )
{
}

void CellArray::Cell::Draw( Graphics& gfx, Color in_c )
{
	const int top_left_x = loc.x + offset;
	const int top_left_y = loc.y + offset;
	const int bottom_right_x = loc.x + dimension - offset;
	const int bottom_right_y = loc.y + dimension - offset;
	gfx.DrawRect( top_left_x, top_left_y, bottom_right_x, bottom_right_y, c );
}

void CellArray::Cell::Draw( Graphics& gfx )
{
	Draw( gfx, c );
}

CellArray::CellArray( const Location& in_loc, int in_dimension )
	:
	loc(in_loc),
	dimension0(in_dimension),
	dimension1(in_dimension)
{
	for( int i = 0; i < in_dimension; i++ )
	{
		for( int j = 0; j < in_dimension; j++ )
		{
			cells.push_back( Cell( loc, i, j ) );
		}
	}
}

CellArray::CellArray( const Location& in_loc, int in_dimension0, int in_dimension1, Color in_c )
	:
	loc( in_loc ),
	dimension0( in_dimension0 ),
	dimension1( in_dimension1 )
{
	for( int i = 0; i < in_dimension0; i++ )
	{
		for( int j = 0; j < in_dimension1; j++ )
		cells.emplace_back( loc, i, j, in_c );
	}
}

void CellArray::Draw( Graphics& gfx )
{
	for( int i = 0; i < cells.size(); i++ )
	{
		cells[i].Draw( gfx );
	}
}

bool CellArray::MouseIsOnArray( const Mouse& mouse ) const
{
	const Location mouse_loc = Location( mouse.GetPosX(), mouse.GetPosY() );
	const Location right_bottom = Location( dimension0, dimension1 ) * Cell::dimension;
	return mouse_loc.x >= loc.x &&
		mouse_loc.x <= right_bottom.x &&
		mouse_loc.y >= loc.y &&
		mouse_loc.y <= right_bottom.y;
}

Location CellArray::GetIdx( const Location& in_loc ) const
{
	const Location locRelativeToBoard = in_loc - loc;
	return locRelativeToBoard / Cell::dimension;
}

void CellArray::SelectFirst( int row_idx, int col_idx )
{
	selectedFirst = &cells[row_idx * dimension0 + col_idx];
}

void CellArray::SelectSecond( int row_idx, int col_idx )
{
	selectedSecond = &cells[row_idx * dimension0 + col_idx];
}

void CellArray::DeselectFirst()
{
	selectedFirst = nullptr;
}

void CellArray::DeselectBoth()
{
	selectedFirst = nullptr;
	selectedSecond = nullptr;
}

void CellArray::Cell::PutPiece( std::shared_ptr<Piece> in_piece )
{
	assert( !piece );
	piece = in_piece;
}

void CellArray::Cell::RemovePiece()
{
	assert( piece );
	piece = nullptr;
}

void CellArray::Cell::MovePieceTo( Cell& nxt_pos )
{
	assert( piece );
	if( nxt_pos.piece )
	{
		nxt_pos.RemovePiece();
	}
	nxt_pos.piece = std::move( piece );
}