#pragma once

#include "Graphics.h"
#include "Location.h"
#include "Piece.h"
#include <optional>

class Pawn : public Piece
{
public:
	Pawn( class Cell& cell, bool in_isLightSide );
	void Move( Board& brd ) override;
};