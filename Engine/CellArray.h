#pragma once

#include "Graphics.h"
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
		Cell( const Location& in_loc, int row_idx, int col_idx );
		void Draw( Graphics& gfx, Color in_c );
		void Draw( Graphics& gfx);
	public:
		static constexpr int offset = 1;
		static constexpr int dimension = 75;
		const Color c;
		const Location loc;
		std::shared_ptr<Piece> p;
	};
public:
	CellArray( const Location& in_loc, int in_dimension );
	CellArray( const Location& in_loc, int in_dimension1, int in_dimension2, Color in_c );
	void Draw( Graphics& gfx );
public:
	static constexpr Color lightCell = Color( 238, 238, 210 );
	static constexpr Color darkCell = Color( 118, 150, 86 );
	static constexpr Color selectedCell = Color( 0, 0, 255 );
private:
	const int dimension0;
	const int dimension1;
	const Location loc;
	std::vector<Cell> cells;
};