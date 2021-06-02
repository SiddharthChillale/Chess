#pragma once

#include "Graphics.h"
#include "Mouse.h"
#include "CellArray.h"
#include "Location.h"
#include "Player.h"
#include <vector>
#include <memory>
#include <optional>

class Board
{
public:
	Board( const Location& loc, int dimension );
	void Draw( Graphics& gfx ) const;
	void ProcessInput( const Graphics& gfx, const Mouse& mouse );
	void PutPieces( Player& player, bool isLightSide );
	bool PathIsFree( const Location& move_vec ) const;
	Cell& GetCurrentCell();
	Cell& GetNextCell();
	const Cell& GetCurrentCell() const;
	const Cell& GetNextCell() const;
	void DeselectLastCell();
	void DeselectAllCells();
	bool GetCurrentTurn() const;
	void SetNextSideMove();
	void PerformMovement();

	Location GetIdx( const Location& loc ) const;
	Cell& GetCell( const Location& locIdx );
	const Cell& GetCell( const Location& locIdx ) const;
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
	bool IsKnightMove( const Location& move_vec ) const;
	Location GetEnPasantTarget( const Location& move_vec ) const;
	bool TargetIsEnPasant( const Location& target ) const;
	bool NextIsFree() const;
	bool NextIsEnemy() const;
private:
	Player light;
	Player dark;
	CellArray arr;
	bool isLightSideMove = true;
	bool isReleasedLeft = true;
};