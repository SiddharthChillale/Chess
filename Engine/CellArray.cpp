#include "CellArray.h"

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