#pragma once

#include "Graphics.h"
#include "Location.h"
#include "Piece.h"
#include <memory>

class Cell
{
public:
	Cell( const Location& brd_loc, int x, int y );
	void Draw( Graphics& gfx, bool isSelected = false ) const;
	static int GetDimension();
	Location GetLocation() const;
	bool IsFree() const;
	bool PieceSide() const;
public:
	void PutPiece( std::unique_ptr<Piece> in_piece );
	void RemovePiece();
	void MovePieceTo( Cell& nxt_pos );
private:
	std::unique_ptr<Piece> piece;
	const Location loc;
	const Color c;
	static constexpr int dimension = 75;
	static constexpr int offset = 1;
	static constexpr Color lightColor = Color( 238, 238, 210 );
	static constexpr Color darkColor = Color( 118, 150, 86 );
	static constexpr Color selectedColor = Color( 0, 0, 255 );
};