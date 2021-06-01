#pragma once

#include "Graphics.h"
#include "Location.h"

class Piece
{
public:
	Piece( class Cell& cell, bool in_isLightSide);
	virtual void Move( class Board& brd, const Location& move_vec, Cell& nxt_pos ) = 0;
	void Draw( Graphics& gfx) const;
	bool PieceSide() const;
	bool IsEnPasant() const;
	bool IsAlive() const;
	static Location GetMoveVec( const Board& brd, const Cell& cur_pos, const Cell& nxt_pos );
	void RecordDeath();
	void TurnOffEnPasant();
protected:
	static Location GetNormalizedMove(const Location& move_vec );
	bool IsOneCellRange( const Location& move_vec ) const;
	bool IsDiagonal( const Location& move_vec ) const;
	bool IsHorizontal( const Location& move_vec ) const;
	bool IsVertical( const Location& move_vec ) const;
	bool PathIsFree( const Board& brd, const Location& move_vec, const Cell& nxt_pos ) const;
	bool IsFreeCell( const Cell& nxt_pos ) const;
	bool IsEnemyCell( const Cell& nxt_pos ) const;
protected:
	Cell* cell;
	const bool isLightSide;
	const Color c;
	bool isAlive = true;
	bool isMoved = false;
	bool isEnPasant = false;
	static constexpr Color lightSideColor = Color( 186, 202, 68 );
	static constexpr Color darkSideColor = Color( 101, 67, 33 );
};