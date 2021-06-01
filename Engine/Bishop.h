#pragma once

#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop( class CellArray::Cell& cell, bool in_isLightSide );
	void Move( class Board& brd ) override;
};