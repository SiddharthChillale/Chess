#include "CellArray.h"
#include <cassert>

CellArray::CellArray( const Location& in_loc, int in_dimension )
	:
	location( in_loc ),
	dimension0( in_dimension ),
	dimension1( in_dimension ),
	selectedCells( dimension0 * dimension1, nullptr )
{
	for( int i = 0; i < in_dimension; i++ )
	{
		for( int j = 0; j < in_dimension; j++ )
		{
			const Location cell_loc = in_loc + Location( i, j ) * Cell::dimension;
			const Color cell_color = ((i + j) % 2) ? CellArray::darkCell : CellArray::lightCell;
			cells.push_back( Cell( cell_loc, i, j, cell_color ) );
		}
	}
}

CellArray::CellArray( const Location& in_loc, int in_dimension0, int in_dimension1, Color in_c )
	:
	location( in_loc ),
	dimension0( in_dimension0 ),
	dimension1( in_dimension1 )
{
	for( int i = 0; i < in_dimension0; i++ )
	{
		for( int j = 0; j < in_dimension1; j++ )
		{
			const Location cell_loc = in_loc + Location( i, j ) * Cell::dimension;
			cells.emplace_back( cell_loc, i, j, in_c );
		}
	}
}

void CellArray::Draw( Graphics& gfx ) const
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
	return mouse_loc.x >= location.x &&
		mouse_loc.x <= right_bottom.x &&
		mouse_loc.y >= location.y &&
		mouse_loc.y <= right_bottom.y;
}

Location CellArray::GetIdx( const Location& in_loc ) const
{
	const Location locRelativeToBoard = in_loc - location;
	return locRelativeToBoard / Cell::dimension;
}

int CellArray::selectedCellsCount() const
{
	return lastSelected;
}

bool CellArray::IsSelected( const Cell& cell ) const
{
	for( int i = 0; i < lastSelected; i++ )
	{
		if( &cells[i] == &cell )
		{
			return true;
		}
	}
	return false;
}

void CellArray::Select( Cell& cell )
{
	assert( lastSelected < dimension0 * dimension1 );
	selectedCells[lastSelected] = &cell;
	lastSelected++;
}

void CellArray::DeselectLast()
{
	assert( lastSelected > 0 );
	selectedCells[lastSelected] = nullptr;
	lastSelected--;
}

void CellArray::DeselectAll()
{
	while( lastSelected >= 0 )
	{
		selectedCells[lastSelected] = nullptr;
		lastSelected--;
	}
}

const Cell& CellArray::operator[]( const Location& loc ) const
{
	return cells[loc.x * dimension0 + loc.y];
}

Cell& CellArray::operator[]( const Location& loc )
{
	return cells[loc.x * dimension0 + loc.y];
}

Cell& CellArray::GetSelected( int idx )
{
	return cells[idx];
}

const Cell& CellArray::GetSelected( int idx ) const
{
	return cells[idx];
}