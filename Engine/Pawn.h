#pragma once

#include "Graphics.h"
#include "Location.h"
#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn( const class Cell& cell, bool in_isLightSide );
	void Move( Cell& cur_pos, Cell& nxt_pos ) override;
private:
	bool IsForwardMove( const Location& move_vec ) const;
	bool IsFastForwardMove( const Board& brd, const Location& move_vec, const Cell& nxt_pos ) const;
	bool IsStepForwardMove( const Location& move_vec, const Cell& nxt_pos ) const;
	bool IsDirectAttack( const Location& move_vec, const Cell& nxt_pos ) const;
	bool IsFFWeaknessAttak( const Location& move_vec, const Cell& nxt_pos ) const;
	bool IsPromotion( const Location& move_vec, const Cell& nxt_pos ) const;
private:
	bool fastForwardWeakness = false;
};