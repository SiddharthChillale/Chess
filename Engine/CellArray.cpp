#include "CellArray.h"
#include <cassert>

CellArray::Cell::Cell( const Location& in_loc, int row_idx, int col_idx, Color in_c )
	:
	location( in_loc ),
	color( in_c )
{
}

void CellArray::Cell::Draw( Graphics& gfx, Color in_c ) const
{
	const int top_left_x = location.x + offset;
	const int top_left_y = location.y + offset;
	const int bottom_right_x = location.x + dimension - offset;
	const int bottom_right_y = location.y + dimension - offset;
	gfx.DrawRect( top_left_x, top_left_y, bottom_right_x, bottom_right_y, in_c );
}

void CellArray::Cell::Draw( Graphics& gfx ) const
{
	Draw( gfx, color );
}

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

const CellArray::Cell& CellArray::operator[]( const Location& loc ) const
{
	return cells[loc.x * dimension0 + loc.y];
}

CellArray::Cell& CellArray::operator[]( const Location& loc )
{
	return cells[loc.x * dimension0 + loc.y];
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

CellArray::Cell& CellArray::GetSelected( int idx )
{
	return cells[idx];
}

const CellArray::Cell& CellArray::GetSelected( int idx ) const
{
	return cells[idx];
}

CellArray::Cell& CellArray::GetSelected( int idx )
{
	return cells[idx];
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

bool CellArray::Cell::IsFree() const
{
	return !bool( piece );
}

bool CellArray::Cell::PieceSide() const
{
	assert( piece );
	return piece->PieceSide();
}

bool CellArray::Cell::IsEnPasant() const
{
	return piece->IsEnPasant();
}

bool CellArray::Cell::IsAlive() const
{
	assert( piece );
	return piece->IsAlive();
}

void CellArray::Cell::RecordDeath()
{
	piece->RecordDeath();
}

void CellArray::Cell::turnOffEnPassant()
{
	piece->TurnOffEnPasant();
}