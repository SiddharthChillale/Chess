#pragma once

#include "Graphics.h"
#include "Mouse.h"
#include "Cell.h"
#include "Location.h"
#include <vector>
#include <memory>
#include <optional>

class Board
{
public:
	Board();
	Location GetLocation() const;
	void Draw( Graphics& gfx ) const;
	bool MouseIsOnBoard( const Graphics& gfx, const Mouse& mouse ) const;
	int GetCell_idx( const Mouse& mouse ) const;
	Cell& GetCell( int cell_dim1, int cell_dim2 );
	void PorcessInput( const Graphics& gfx, const Mouse& mouse );
private:
	void PutPiecesInCells();
private:
	const Location loc = Location( 100, 0 );
	static constexpr int dimension = 8;
	std::vector<Cell> cells;
	std::optional<int> idxCurrentCell;
	std::optional<int> idxTargetCell;
	bool isReleasedLeft = true;
};