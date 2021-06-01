#pragma once

#include "Graphics.h"
#include "Mouse.h"
#include "Location.h"
#include "Piece.h"
#include <memory>
#include <vector>

class CellArray
{
public:
	class Cell
	{
	public:
		Cell( const Location& in_loc, int row_idx, int col_idx, Color in_c );
		void Draw( Graphics& gfx, Color in_c ) const;
		void Draw( Graphics& gfx) const;

		bool IsFree() const;
		bool PieceSide() const;
		bool IsEnPasant() const;
		bool IsAlive() const;
		void RecordDeath();
		void turnOffEnPassant();

		void PutPiece( std::shared_ptr<Piece> in_piece );
		void RemovePiece();
		void MovePieceTo( Cell& nxt_pos );

		static void PerformMovement( Cell& current, Cell& next);
	public:
		static constexpr int offset = 1;
		static constexpr int dimension = 75;
		const Color color;
		const Location location;
		std::shared_ptr<Piece> piece;
	};
public:
	CellArray( const Location& in_loc, int in_dimension );
	CellArray( const Location& in_loc, int in_dimension1, int in_dimension2, Color in_c );
	void Draw( Graphics& gfx ) const;
	bool MouseIsOnArray( const Mouse& mouse ) const;
	Location GetIdx( const Location& in_loc ) const;
	const Cell& operator[]( const Location& loc ) const;
	Cell& operator[]( const Location& loc );
	int selectedCellsCount() const;

	bool IsSelected( const Cell& cell ) const;
	Cell& GetSelected( int idx );
	void Select( Cell& cell );
	void DeselectLast();
	void DeselectAll();
public:
	static constexpr Color lightCell = Color( 238, 238, 210 );
	static constexpr Color darkCell = Color( 118, 150, 86 );
	static constexpr Color selectedCell = Color( 0, 0, 255 );
	const int dimension0;
	const int dimension1;
	const Location location;
private:
	std::vector<Cell> cells;
	std::vector<Cell*> selectedCells;
	int lastSelected = 0;
};