#include "../conutils/color.hpp"
#include "../conutils/coordops.hpp"
#include "../conutils/cursor.hpp"
#include "../eventhandler.hpp"
#include <cassert>
#include "field.hpp"

unsigned const autodropIntervalInMs = 300;

namespace Game
{
	bool Field::IsColliding(std::vector<COORD> const& blockPositions) const
	{
		for (auto const& b : blockPositions)
		{
			// Out of bounds check
			if (b.X < position.X || b.X >= (position.X + size.X) || b.Y < position.Y || b.Y >= (position.Y + size.Y))
				return true;

			unsigned const index = (b.X - position.X) + (b.Y - position.Y) * size.X;
			if (occupiedBlocks[index])
			{
				return true;
			}
		}

		return false;
	}

	void Field::Merge(std::vector<COORD> const& blockPositions)
	{
		for (auto const& b : blockPositions)
		{
			// Out of bounds check
			if (b.X < position.X || b.X >= (position.X + size.X) || b.Y < position.Y || b.Y >= (position.Y + size.Y))
				continue;

			unsigned const index = (b.X - position.X) + (b.Y - position.Y) * size.X;
			occupiedBlocks[index] = true;
		}

		SpawnTetromino();
	}

	void Field::SpawnTetromino()
	{
		Color::Set(Color::Color());
		auto const previewblocks = previewTetroPtr->GetState().GetTranslatedBlocks();
		for (auto const& b : previewblocks)
		{
			Cursor::Set(b);
			std::cout << ' ';
		}

		currentTetroPtr.swap(previewTetroPtr);
		currentTetroPtr->SetPosition(tetroSpawnPosition);
		currentTetroPtr->Draw();

		// TODO use previewTetro spawn coords
		previewTetroPtr = std::make_unique<Tetromino>(tetrominoFactory.GetRandomTetromino(previewTetroSpawnPosition));
		previewTetroPtr->Draw();
	}

	bool Field::HandleInput()
	{
		assert(currentTetroPtr != nullptr);

		EventHandler const& evHandler = EventHandler::GetInstance();
		if (evHandler.WasActionReleased(PlayerActions::RotateLeft))
		{
			currentTetroPtr->RotateLeft();
		}
		else if (evHandler.WasActionReleased(PlayerActions::RotateRight))
		{
			currentTetroPtr->RotateRight();
		}

		SHORT X_movement = 0;	
		if (evHandler.WasActionReleased(PlayerActions::MoveLeft))
		{
			X_movement -= 1;
		}
		else if (evHandler.WasActionReleased(PlayerActions::MoveRight))
		{
			X_movement += 1;
		}

		currentTetroPtr->Move(X_movement);

		if (evHandler.WasActionPressed(PlayerActions::MoveDown))
		{
			return true;
		}
	}

	void Field::Update(unsigned const elapsedMs)
	{
		bool drop = false;

		elapsedTime += elapsedMs;
		if (elapsedTime >= autodropIntervalInMs)
		{
			drop = true;
			elapsedTime = 0U;
		}

		TetrominoState const currentState = currentTetroPtr->GetState();
		drop = drop || HandleInput();
		
		TetrominoState candidateState = currentTetroPtr->GetState();
		if (drop)
		{
			candidateState.position.Y += 1;
			if (IsColliding(candidateState.GetTranslatedBlocks()))
			{
				// Illegal move ?
				candidateState.position.Y -= 1;
				if (IsColliding(candidateState.GetTranslatedBlocks()))
				{
					// Yes
					candidateState = currentState;

					candidateState.position.Y += 1;
					if (IsColliding(candidateState.GetTranslatedBlocks()))
					{
						Merge(currentState.GetTranslatedBlocks());
						return;
					}
				}
				else
				{
					Merge(candidateState.GetTranslatedBlocks());			
					return;
				}
			}		
		}
		else
		{
			if (IsColliding(candidateState.GetTranslatedBlocks()))
			{
				// Illegal move
				candidateState = currentState;
			}
		}

		currentTetroPtr->SetState(candidateState);

		if (drop || currentState != candidateState)
		{
			currentState.Draw(Color::Color(), ' ');
			currentTetroPtr->Draw();
		}
	}

	Field::Field(COORD _position, COORD _size)
		: position(_position),
		size(_size),
		tetroSpawnPosition({ _position.X + _size.X / 2, _position.Y }),
		previewTetroSpawnPosition({_position.X + _size.X + 3, _position.Y + 3}),
		tetrominoFactory(73816),
		previewTetroPtr(nullptr),
		currentTetroPtr(nullptr),
		elapsedTime(0)
	{
		occupiedBlocks.resize(_size.X * _size.Y);

		for (SHORT y = position.Y; y < position.Y + size.Y; ++y)
		{
			Cursor::Set(COORD{ position.X, y });
			Color::Set(Color::Color()); // Black and white
			for (SHORT x = position.X; x < position.X + size.X; ++x)
			{
				std::cout << ' ';
			}
		}

		previewTetroPtr = std::make_unique<Tetromino>(tetrominoFactory.GetRandomTetromino(previewTetroSpawnPosition));
		SpawnTetromino();
	}
}
