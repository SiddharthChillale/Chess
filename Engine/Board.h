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
	int GetCell_idx( const Location& loc ) const;
	void PorcessInput( const Graphics& gfx, const Mouse& mouse );
private:
	const Location loc = Location( 100, 0 );
	static constexpr int dimension = 8;
	std::vector<Cell> cells;
	std::optional<int> idxCurrentCell;
	std::optional<int> idxTargetCell;
	bool isReleasedLeft = true;
};