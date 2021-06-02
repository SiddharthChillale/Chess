#include "Player.h"
#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

Player::Player( Side side )
{
	isLightSide = bool(side);
	const int rows = 2;
	const int cols = 8;
	
	for( int i = 0; i < cols; i++ )
	{
		pieces.push_back( std::make_shared<Pawn>( *this ) );
	}
	pieces.push_back( std::make_shared<Rook>  ( *this ) );
	pieces.push_back( std::make_shared<Knight>( *this ) );
	pieces.push_back( std::make_shared<Bishop>( *this ) );
	pieces.push_back( std::make_shared<Queen> ( *this ) );
	pieces.push_back( std::make_shared<King>  ( *this ) );
	pieces.push_back( std::make_shared<Bishop>( *this ) );
	pieces.push_back( std::make_shared<Knight>( *this ) );
	pieces.push_back( std::make_shared<Rook>  ( *this ) );
}

void Player::SharePiece( Cell& cell, int idx )
{
	cell.PutPiece( pieces[idx] );
	pieces[idx]->OccupyCell( &cell );
}

void Player::Move( Board& brd, std::shared_ptr<Piece> piece )
{
	movedPiece = piece;
	piece->Move( brd );
}

bool Player::isLastMoved( const std::shared_ptr<Piece> piece )
{
	return piece == movedPiece;;
}

bool Player::IsLightSide() const
{
	return isLightSide;
}

