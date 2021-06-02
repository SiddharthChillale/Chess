#pragma once

#include "Graphics.h"
#include "Location.h"
#include "Piece.h"
#include <optional>

class Pawn : public Piece
{
public:
	Pawn( class Player& in_player );
	void Move( Board& brd ) override;
};