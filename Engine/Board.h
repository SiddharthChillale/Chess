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
	void DeselectLastCell();
	void DeselectAllCells();
	bool GetCurrentTurn() const;
	void SetNextSideMove();
	void PerformMovement();

	Location GetIdx( const Location& loc ) const;
	CellArray::Cell& GetCell( const Location& locIdx );
	const CellArray::Cell& GetCell( const Location& locIdx ) const;
	static Location GetMoveVec( const Location& current, const Location& next );
	static Location GetNormalizedMove( const Location& move_vec );
	bool IsForwardMove( const Location& move_vec ) const;
	bool IsFastForwardMove( const Location& move_vec ) const;
	bool IsStepForwardMove( const Location& move_vec ) const;
	bool IsPromotion( const Location& move_vec ) const;
	bool IsOneCellRange( const Location& move_vec ) const;
	bool IsDiagonal( const Location& move_vec ) const;
	bool IsHorizontal( const Location& move_vec ) const;
	bool IsVertical( const Location& move_vec ) const;
	Location GetEnPasantTarget( const Location& move_vec ) const;
	bool TargetIsEnPasant( const Location& target ) const;
	bool NextIsFree() const;
	bool NextIsEnemy() const;
private:
	CellArray arr;
	bool isLightSideMove = true;
	bool isReleasedLeft = true;
};