#pragma once

#include "Graphics.h"
#include "Cell.h"
#include "Location.h"
#include <vector>
#include <memory>

class Board
{
public:
	Board();
	Location GetLocation() const;
	void Draw( Graphics& gfx ) const;
private:
	const Location loc = Location( 100, 0 );
	static constexpr int dimension = 8;
	std::vector<Cell> cells;
};