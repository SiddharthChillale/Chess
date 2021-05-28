#pragma once

#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop( class Cell& cell, bool in_isLightSide );
	void Move( class Board& brd, const Location& move_vec, Cell& nxt_pos ) override;
};