#include "Board.h"

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
		cells[i].Draw( gfx );
	}
}
