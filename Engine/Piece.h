#pragma once

#include "Graphics.h"
#include "Location.h"

class Piece
{
public:
	Piece( const class Cell& cell, bool in_isLightSide);
	virtual void Move( Cell& cur_pos, Cell& nxt_pos ) = 0;
	void Draw( Graphics& gfx) const;
	bool PieceSide() const;
protected:
	bool IsEnemy( const Cell& nxt_pos ) const;
	static Location GetMoveVec( const Cell& cur_pos, const Cell& nxt_pos );
	static Location GetNormalizedMove(const Location& move_vec );
	bool IsDiagonal( const Location& move_vec ) const;
	bool IsHorizontal( const Location& move_vec ) const;
	bool IsVertical( const Location& move_vec ) const;
	bool IsLongPath( const Location& move_vec, const Cell& nxt_pos ) const;
	bool PathIsFree( const class Board& brd, const Location& move_vec, const Cell& nxt_pos ) const;
	bool IsFreeCell( const Cell& nxt_pos ) const;
	bool IsEnemyCell( const Cell& nxt_pos ) const;
protected:
	const Cell* cell;
	const bool isLightSide;
	const Color c;
	static constexpr Color lightSideColor = Color( 186, 202, 68 );
	static constexpr Color darkSideColor = Color( 101, 67, 33 );
};