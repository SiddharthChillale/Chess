#pragma once

#include "Piece.h"

class Queen : public Piece
{
public:
	Queen( class Cell& cell, bool in_isLightSide );
	void Move( class Board& brd ) override;
};