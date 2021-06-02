#include "Board.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Rook.h"
#include "Knight.h"
#include "King.h"
#include "Queen.h"
#include <cassert>

Board::Board( const Location& loc, int dimenstion )
	:
	arr( loc, dimenstion ),
	light( Player::Side::Light ),
	dark( Player::Side::Dark )
{
	const bool lightPlayer = true;
	const bool darkPlayer = !lightPlayer;
	PutPieces( light, lightPlayer );
	PutPieces( dark, darkPlayer );
}

void Board::Draw( Graphics& gfx ) const
{
	arr.Draw( gfx );
}

void Board::SetNextSideMove()
{
	isLightSideMove = !isLightSideMove;
}

void Board::PerformMovement()
{
	const Location move_vec = GetMoveVec( GetCurrentCell().location, GetNextCell().location );
	GetCurrentCell().piece->Move( *this );
}

bool Board::GetCurrentTurn() const
{
	return isLightSideMove;
}

void Board::ProcessInput( const Graphics& gfx, const Mouse& mouse )
{
	Player* current_player = isLightSideMove ? &light : &dark;
	if( isReleasedLeft && mouse.LeftIsPressed() && arr.MouseIsOnArray( mouse ) )
	{
		isReleasedLeft = false;
		const Location mouse_loc_idx = Location( mouse.GetPosX(), mouse.GetPosY() );
		Cell& cell_to_select = arr[GetIdx( mouse_loc_idx )];
		if( arr.selectedCellsCount() == 0 )
		{
			if( !cell_to_select.IsFree() && (cell_to_select.PieceSide() == isLightSideMove) )
			{
				arr.Select( cell_to_select );
			}
		}
		else if( arr.IsSelected( cell_to_select ) )
		{
			arr.DeselectAll();
		}
		else if( arr.selectedCellsCount() == 1 )
		{
			arr.Select( cell_to_select );
			current_player->Move( *this, GetCurrentCell().piece );
		}
	}
	if( !mouse.LeftIsPressed() )
	{
		isReleasedLeft = true;
	}
}

void Board::PutPieces( Player& player, bool isLightSide )
{

	int firstRow;
	int secondRow;
	if( isLightSide )
	{
		firstRow = 6;
		secondRow = 7;
	}
	else
	{
		firstRow = 1;
		secondRow = 0;
	}
	int piece_idx = 0;
	const int incr_val = secondRow - firstRow;
	for( int i = firstRow; i != firstRow + 2 * incr_val; i += incr_val )
	{
		for( int j = 0; j < arr.dimension1; j++ )
		{
			Cell& cell = arr[Location( j, i )];
			player.SharePiece( cell, piece_idx );
			piece_idx++;
		}
	}
}

bool Board::PathIsFree( const Location& move_vec ) const
{
	const Location& norm_move_vec = Board::GetNormalizedMove( move_vec );
	const Location destination = arr.GetIdx( GetNextCell().location );
	const Location current = arr.GetIdx( GetCurrentCell().location );
	Location cur_pos = current + norm_move_vec;
	while( cur_pos != destination )
	{
		const bool isNotFree = !arr[cur_pos].IsFree();
		if( isNotFree )
		{
			return false;
		}
		cur_pos += norm_move_vec;
	}
	return true;
}

Cell& Board::GetCurrentCell()
{
	return arr.GetSelected( 0 );
}

Cell& Board::GetNextCell()
{
	return arr.GetSelected( 1 );
}

const Cell& Board::GetCurrentCell() const
{
	return arr.GetSelected( 0 );
}

const Cell& Board::GetNextCell() const
{
	return arr.GetSelected( 1 );
}

void Board::DeselectLastCell()
{
	arr.DeselectLast();
}

void Board::DeselectAllCells()
{
	arr.DeselectAll();
}

Location Board::GetIdx( const Location& loc ) const
{
	return arr.GetIdx( loc );
}

Cell& Board::GetCell( const Location& locIdx )
{
	return arr[locIdx];
}

const Cell& Board::GetCell( const Location& locIdx ) const
{
	return arr[locIdx];
}

Location Board::GetMoveVec( const Location& current, const Location& next )
{
	const Location move_vec = next - current;
	return move_vec;
}

Location Board::GetNormalizedMove( const Location& move_vec )
{
	Location result( 0, 0 );
	assert( move_vec != result );

	if( move_vec.x != 0 )
	{
		return move_vec / abs( move_vec.x );
	}
	return move_vec / abs( move_vec.y );
}

bool Board::IsOneCellRange( const Location& move_vec ) const
{
	const int abs_x = abs( move_vec.x );
	const int abs_y = abs( move_vec.y );
	return (abs_x < 2) && (abs_y < 2);
}

bool Board::IsDiagonal( const Location& move_vec ) const
{
	return abs( move_vec.x ) == abs( move_vec.y );
}

bool Board::IsHorizontal( const Location& move_vec ) const
{
	return move_vec.y == 0;
}

bool Board::IsVertical( const Location& move_vec ) const
{
	return move_vec.x == 0;
}

bool Board::NextIsFree() const
{
	return GetNextCell().IsFree();
}

bool Board::NextIsEnemy() const
{
	if( GetNextCell().IsFree() )
	{
		return false;
	}
	return GetCurrentCell().PieceSide() != GetNextCell().PieceSide();
}

bool Board::IsForwardMove( const Location& move_vec ) const
{
	if( GetCurrentCell().piece->IsLightSide() )
	{
		return move_vec.y < 0;
	}
	return move_vec.y > 0;
}

bool Board::IsFastForwardMove( const Location& move_vec ) const
{
	assert( IsForwardMove( move_vec ) && GetNextCell().IsFree() );
	return  (std::abs( move_vec.y ) == 2) && (std::abs( move_vec.x ) == 0) && (!GetCurrentCell().piece->IsMoved());
}

bool Board::IsStepForwardMove( const Location& move_vec ) const
{
	assert( IsForwardMove( move_vec ) && GetNextCell().IsFree() );
	return (std::abs( move_vec.x ) == 0) && (std::abs( move_vec.y ) == 1);
}

Location Board::GetEnPasantTarget( const Location& move_vec ) const
{
	const Location target = GetIdx( GetCurrentCell().location ) + Location( move_vec.x, move_vec.y * 0 );
	return target;
}

bool Board::TargetIsEnPasant( const Location& target ) const
{
	const Cell& MaybeEnPasant = GetCell( target );
	if( !MaybeEnPasant.IsFree() &&
		(GetCurrentCell().piece->PieceSide() != MaybeEnPasant.PieceSide()) && MaybeEnPasant.IsEnPasant() )
	{
		return true;
	}
	return false;
}

bool Board::IsKnightMove( const Location& move_vec ) const
{
	return std::abs( move_vec.x ) + std::abs( move_vec.y ) == 3;
}