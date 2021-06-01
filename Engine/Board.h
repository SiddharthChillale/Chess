#pragma once

#include "Graphics.h"
#include "Mouse.h"
#include "CellArray.h"
#include "Location.h"
#include <vector>
#include <memory>
#include <optional>

class Board
{
public:
	Board( const Location& loc, int dimension );
	void Draw( Graphics& gfx ) const;
	void ProcessInput( const Graphics& gfx, const Mouse& mouse );
	bool GetCurrentTurn() const;
	void SetNextSideMove();
private:
	CellArray arr;
	bool isLightSideMove = true;
	bool isReleasedLeft = true;
};