#pragma once

#include "Piece.h"

class King :public Piece
{
public:
	King( class Player& in_player );
	void Move( class Board& brd ) override;
};