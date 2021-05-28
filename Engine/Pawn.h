#pragma once

#include "Graphics.h"
#include "Location.h"
#include "Piece.h"
#include <optional>

class Pawn : public Piece
{
public:
	Pawn( class Cell& cell, bool in_isLightSide );
	void Move( Board& brd, const Location& move_vec, Cell& nxt_pos ) override;
private:
	bool IsForwardMove( const Location& move_vec ) const;
	bool IsFastForwardMove( const Location& move_vec, const Cell& nxt_pos ) const;
	bool IsStepForwardMove( const Location& move_vec, const Cell& nxt_pos ) const;
	bool IsPromotion( const Location& move_vec, const Cell& nxt_pos ) const;
	Location GetEnPasantTarget( const Board& brd, const Location& move_vec ) const;
	Cell& GetEnPasant( Board& brd, const Location& move_vec );
	bool TargetIsEnPasant( const Board& brd, const Location& target ) const;
};