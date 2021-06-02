#pragma once

#include "Piece.h"

class Knight : public Piece
{
public:
	Knight( class Player& in_player );
	void Move( class Board& brd ) override;
};