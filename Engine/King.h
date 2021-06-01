#pragma once

#include "Piece.h"

class King :public Piece
{
public:
	King( class Cell& cell, bool in_isLightSide );
	void Move( class Board& brd ) override;
};