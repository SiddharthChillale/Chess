#pragma once

#include "Piece.h"

class Rook : public Piece
{

public:
	Rook( class Cell& cell, bool in_isLightSide );
	void Move( class Board& brd ) override;
};