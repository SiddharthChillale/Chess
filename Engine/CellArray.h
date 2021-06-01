#pragma once

#include "Graphics.h"
#include "Mouse.h"
#include "Location.h"
#include "Piece.h"
#include <memory>
#include <vector>

class CellArray
{
private:
	class Cell
	{
	public:
		Cell( const Location& in_loc, int row_idx, int col_idx, Color in_c );
		void Draw( Graphics& gfx, Color in_c );
		void Draw( Graphics& gfx);

		bool IsFree() const;
		bool PieceSide() const;
		bool IsEnPasant() const;
		bool IsAlive() const;
		void RecordDeath();
		void turnOffEnPassant();

		void PutPiece( std::shared_ptr<Piece> in_piece );
		void RemovePiece();
		void MovePieceTo( Cell& nxt_pos );
	public:
		static constexpr int offset = 1;
		static constexpr int dimension = 75;
		const Color c;
		const Location loc;
		std::shared_ptr<Piece> piece;
	};
public:
	CellArray( const Location& in_loc, int in_dimension );
	CellArray( const Location& in_loc, int in_dimension1, int in_dimension2, Color in_c );
	void Draw( Graphics& gfx );
	bool MouseIsOnArray( const Mouse& mouse ) const;
	Location GetIdx( const Location& in_loc ) const;

	void SelectFirst( int row_idx, int col_idx);
	void SelectSecond( int row_idx, int col_idx);
	void DeselectFirst();
	void DeselectBoth();
public:
	static constexpr Color lightCell = Color( 238, 238, 210 );
	static constexpr Color darkCell = Color( 118, 150, 86 );
	static constexpr Color selectedCell = Color( 0, 0, 255 );
	const int dimension0;
	const int dimension1;
	const Location loc;
private:
	std::vector<Cell> cells;
	Cell* selectedFirst;
	Cell* selectedSecond;
};