#pragma once

#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop( class Player& in_player );
	void Move( class Board& brd ) override;
};