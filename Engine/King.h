#pragma once

#include "Piece.h"

class King :public Piece
{
public:

	King( class CellArray::Cell& cell, bool in_isLightSide );
	void Move( class Board& brd ) override;
};