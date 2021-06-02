#pragma once

#include "Piece.h"

class Queen : public Piece
{
public:
	Queen( class Player& in_player );
	void Move( class Board& brd ) override;
};