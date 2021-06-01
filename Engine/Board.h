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
	bool PathIsFree( const Location& move_vec ) const;
	CellArray::Cell& GetCurrentCell();
	CellArray::Cell& GetNextCell();
	const CellArray::Cell& GetCurrentCell() const;
	const CellArray::Cell& GetNextCell() const;
	bool GetCurrentTurn() const;
	void SetNextSideMove();

	static Location GetNormalizedMove( const Location& move_vec );
	bool IsOneCellRange( const Location& move_vec ) const;
	bool IsDiagonal( const Location& move_vec ) const;
	bool IsHorizontal( const Location& move_vec ) const;
	bool IsVertical( const Location& move_vec ) const;
	bool NextIsFree() const;
	bool NextIsEnemy() const;
private:
	CellArray arr;
	bool isLightSideMove = true;
	bool isReleasedLeft = true;
};