#pragma once

#include "Graphics.h"
#include "Mouse.h"
#include "Location.h"
#include "Piece.h"
#include "Cell.h"
#include <memory>
#include <vector>

class CellArray
{
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
	const Cell& GetSelected( int idx ) const;
	void Select( Cell& cell );
	void DeselectLast();
	void DeselectAll();
public:
	static constexpr Color lightCell = Color( 238, 238, 210 );
	static constexpr Color darkCell = Color( 118, 150, 86 );
	static constexpr Color colorSelectedCell = Color( 0, 0, 255 );
	const int dimension0;
	const int dimension1;
	const Location location;
private:
	std::vector<Cell> cells;
	std::vector<Cell*> selectedCells;
	int lastSelected = 0;
};