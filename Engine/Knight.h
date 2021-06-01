#pragma once

#include "Piece.h"

class Knight : public Piece
{
public:
	Knight( class Cell& cell, bool in_isLightSide );
	void Move( class Board& brd ) override;
};