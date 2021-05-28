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
	int GetCell_idx( const Location& pixel_dim ) const;
	const Cell& GetConstCell( const Location& cell_dim ) const;
	Location PixelToCellDim( const Location& piexel_dim ) const;
	Cell& GetCell( int cell_dim1, int cell_dim2 );
	void ProcessInput( const Graphics& gfx, const Mouse& mouse );
	bool IsLightSideMove() const;
	bool GetCurrentTurn() const;
	void SetNextSideMove();
	void DeselectTargetCell();
	void DeselectBothCells();
private:
	void PutPawnsInCells();
	void PutBishopsInCells();
	void PutRooksInCells();
private:
	const Location loc = Location( 100, 0 );
	static constexpr int dimension = 8;
	std::vector<Cell> cells;
	std::optional<int> idxCurrentCell;
	std::optional<int> idxTargetCell;
	bool isLightSideMove = true;
	bool isReleasedLeft = true;
};