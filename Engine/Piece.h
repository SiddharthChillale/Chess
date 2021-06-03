#pragma once

#include "Graphics.h"
#include "Location.h"

class Piece
{
public:
	Piece( class Player& in_player );
	virtual void Move( class Board& brd ) = 0;
	void OccupyCell( class Cell* in_cell );
	void Draw( Graphics& gfx) const;
	bool PieceSide() const;
	bool IsEnPasant() const;
	bool IsAlive() const;
	bool IsLightSide() const;
	bool IsMoved() const;
	void RecordMove();
	void TurnOffEnPasant();
	bool operator==( const Piece& rhs )const;
protected:
	Cell* cell = nullptr;
	const Player* owner;
	Color c;
	bool isMoved = false;
	bool isEnPasant = false;
	static constexpr Color lightSideColor = Color( 186, 202, 68 );
	static constexpr Color darkSideColor = Color( 101, 67, 33 );
};