#include "Piece.h"
#include "CellArray.h"
#include "Board.h"
#include <cassert>

Piece::Piece( CellArray::Cell& in_cell, bool in_isLightSide )
	:
	cell( &in_cell ), 
	isLightSide( in_isLightSide ),
	c( in_isLightSide ? lightSideColor : darkSideColor )
{
	
}

void Piece::Draw( Graphics& gfx) const
{
	const int center = CellArray::Cell::dimension / 2;
	const Location global_location = cell->location + Location( center, center );
	gfx.DrawCircle( global_location.x, global_location.y, 25, c );
}

bool Piece::PieceSide() const
{
	return isLightSide;
}

void Piece::RecordDeath()
{
	isAlive = false;
}

void Piece::TurnOffEnPasant()
{
	isEnPasant = false;
}

bool Piece::IsEnPasant() const
{
	return isEnPasant;
}

bool Piece::IsAlive() const
{
	return isAlive;
}

bool Piece::IsLightSide() const
{
	return isLightSide;
}

bool Piece::IsMoved() const
{
	return isMoved;
}

void Piece::RecordMove()
{
	isMoved = true;
}
