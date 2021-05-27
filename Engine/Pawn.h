#pragma once

#include "Graphics.h"
#include "Location.h"
#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn( const class Cell& cell, bool in_isLightSide );
};