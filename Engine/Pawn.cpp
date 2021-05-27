#include "Pawn.h"
#include "Cell.h"

Pawn::Pawn( const Cell& cell, bool in_isLightSide )
	:
	Piece( cell, in_isLightSide )
{
}
