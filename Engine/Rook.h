#pragma once

#include "Piece.h"

class Rook : public Piece
{
public:
	Rook( class Player& in_player );
	void Move( class Board& brd ) override;
};