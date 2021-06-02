#pragma once

#include <vector>
#include <memory>
#include "Piece.h"

class Player
{
public:
	enum class Side
	{
		Dark,
		Light
	};
	Player( Side side );
	void SharePiece( Cell& cell, int idx );
	void Move( class Board& brd, std::shared_ptr<Piece> piece );
	bool isLastMoved( const std::shared_ptr<Piece> piece );
	bool IsLightSide() const;
private:
	bool isLightSide;
	std::vector<std::shared_ptr<Piece>> pieces;
	std::shared_ptr<Piece> movedPiece = nullptr;
};