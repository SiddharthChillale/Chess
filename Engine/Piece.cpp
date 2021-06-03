#include "Piece.h"
#include "Cell.h"
#include "CellArray.h"
#include "Board.h"
#include <cassert>

Piece::Piece( Player& in_player )
{
	owner = &in_player;
	c = owner->IsLightSide() ? lightSideColor : darkSideColor;
}

void Piece::OccupyCell( Cell* in_cell )
{
	cell = in_cell;
}

void Piece::Draw( Graphics& gfx) const
{
	assert( cell );
	const int center = Cell::dimension / 2;
	const Location global_location = cell->location + Location( center, center );
	gfx.DrawCircle( global_location.x, global_location.y, 25, c );
}

bool Piece::PieceSide() const
{
	return owner->IsLightSide();
}

void Piece::TurnOffEnPasant()
{
	isEnPasant = false;
}

bool Piece::operator==( const Piece& rhs ) const
{
	return cell == rhs.cell;
}

bool Piece::IsEnPasant() const
{
	return isEnPasant && owner->isLastMoved( *this );
}

bool Piece::IsAlive() const
{
	return cell;
}

bool Piece::IsLightSide() const
{
	return owner->IsLightSide();
}

bool Piece::IsMoved() const
{
	return isMoved;
}

void Piece::RecordMove()
{
	isMoved = true;
}
