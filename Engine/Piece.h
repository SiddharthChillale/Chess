#pragma once

#include "Graphics.h"
#include "Location.h"

class Piece
{
public:
	Piece( class CellArray::Cell& cell, bool in_isLightSide);
	virtual void Move( class Board& brd, const Location& move_vec, CellArray::Cell& nxt_pos ) = 0;
	void Draw( Graphics& gfx) const;
	bool PieceSide() const;
	bool IsEnPasant() const;
	bool IsAlive() const;
	void RecordDeath();
	void TurnOffEnPasant();
protected:
	CellArray::Cell* cell;
	const bool isLightSide;
	const Color c;
	bool isAlive = true;
	bool isMoved = false;
	bool isEnPasant = false;
	static constexpr Color lightSideColor = Color( 186, 202, 68 );
	static constexpr Color darkSideColor = Color( 101, 67, 33 );
};