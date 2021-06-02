#pragma once

#include "Graphics.h"
#include "Location.h"
#include "Piece.h"
#include "Player.h"
#include <memory>

class Cell
{
public:
	Cell( const Location& in_loc, int row_idx, int col_idx, Color in_c );
	void Draw( Graphics& gfx, Color in_c ) const;
	void Draw( Graphics& gfx ) const;

	bool IsFree() const;
	bool PieceSide() const;
	bool IsEnPasant() const;
	bool IsAlive() const;
	void RecordDeath();
	void turnOffEnPassant();

	void PutPiece( std::shared_ptr<Piece> in_piece );
	void RemovePiece();
	void MovePieceTo( Cell& nxt_pos );

	static void PerformMovement( class Board& brd );
public:
	static constexpr int offset = 1;
	static constexpr int dimension = 75;
	const Color color;
	const Location location;
	std::shared_ptr<Piece> piece;
};