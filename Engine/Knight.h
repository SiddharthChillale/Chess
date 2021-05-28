#pragma once

#include "Piece.h"

class Knight : public Piece
{
public:
	Knight( class Cell& cell, bool in_isLightSide );
	void Move( class Board& brd, const Location& move_vec, Cell& nxt_pos ) override;
	bool IsKnightMove( const Location& move_vec ) const;
};