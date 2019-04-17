#include "../conutils/color.hpp"
#include "../conutils/coordops.hpp"
#include "../conutils/cursor.hpp"
#include "../eventhandler.hpp"
#include "../statemanager.hpp"
#include "../states/gameoverstate.hpp"
#include <cassert>
#include <cstdio>
#include "field.hpp"

unsigned const autodropIntervalInMs = 300;

namespace Game
{
	void Field::DrawScore() const
	{
		Color::Set(Color::Color());
		Cursor::Set(COORD{ position.X + size.X + 2, position.Y + 1 });
		
		std::printf("%05u", score); // Oh boy, we're mixing with C libs now
	}

	bool Field::IsBlockOutOfBounds(COORD const& block) const
	{
		return block.X < position.X || block.X >= (position.X + size.X) || block.Y < position.Y || block.Y >= (position.Y + size.Y);
	}

	bool Field::IsColliding(std::vector<COORD> const& blockPositions) const
	{
		for (auto const& b : blockPositions)
		{
			if (IsBlockOutOfBounds(b))
				return true;

			unsigned const index = (b.X - position.X) + (b.Y - position.Y) * size.X;
			if (occupiedBlocks[index])
			{
				return true;
			}
		}

		return false;
	}

	bool Field::IsRowFull(SHORT const row) const
	{
		SHORT const start = row * size.X;
		for (SHORT i = start; i < start + size.X; ++i)
		{
			if (!occupiedBlocks[i])
				return false;
		}

		return true;
	}

	void Field::PopRow(SHORT const row)
	{
		// Clear row
		Cursor::Set(COORD{ position.X, row + position.Y });
		Color::Set(Color::Color());
		for (SHORT x = 0; x < size.X; ++x)
		{
			std::cout << ' ';
			occupiedBlocks[x + (row * size.X)] = false;
		}

		// Shift everything down
		if (row > 0)
		{
			for (SHORT y = row; y > 0; --y)
			{
				for (SHORT x = 0; x < size.X; ++x)
				{
					// Only copy if there is actually a "block" above us
					if (occupiedBlocks[x + (y - 1) * size.X])
					{
						// Copy
						CHAR_INFO block;
						SMALL_RECT region;
						region.Top = position.Y + (y - 1);
						region.Left = position.X + x;
						region.Bottom = region.Top;
						region.Right = region.Left + 1;

						ReadConsoleOutput(
							GetStdHandle(STD_OUTPUT_HANDLE),
							&block,
							COORD{ 1, 1 },
							COORD{ 0, 0 },
							&region
						);

						occupiedBlocks[x + y * size.X] = true;

						++region.Top;
						++region.Bottom;
						WriteConsoleOutput(
							GetStdHandle(STD_OUTPUT_HANDLE),
							&block,
							COORD{ 1, 1 },
							COORD{ 0, 0 },
							&region
						);

						// Clear
						Cursor::Set(COORD{ x + position.X, (y - 1) + position.Y });
						Color::Set(Color::Color());
						std::cout << ' ';
						occupiedBlocks[x + (y - 1) * size.X] = false;
					}
				}
			}
		}

		// Clear the top row
		Color::Set(Color::Color());
		Cursor::Set(position);
		for (SHORT x = 0; x < size.X; ++x)
		{
			occupiedBlocks[x] = false;
			std::cout << ' ';
		}
	}

	void Field::PopFullRows(SHORT const startRow, SHORT const endRow)
	{
		unsigned rowsPopped = 0;
		for (SHORT y = startRow; y < endRow; ++y)
		{
			if (IsRowFull(y))
			{
				PopRow(y);
				++rowsPopped;
			}
		}

		if (rowsPopped)
		{
			score += rowsPopped * 125;
			DrawScore();
		}
	}

	void Field::Merge(std::vector<COORD> const& blockPositions)
	{
		SHORT minY = size.Y, maxY = 0;
		for (auto const& b : blockPositions)
		{
			if (IsBlockOutOfBounds(b))
				continue;

			if (minY > b.Y)
				minY = b.Y;
			if (maxY < b.Y)
				maxY = b.Y;

			unsigned const index = (b.X - position.X) + (b.Y - position.Y) * size.X;
			occupiedBlocks[index] = true;
		}

		PopFullRows(minY, maxY);
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

		previewTetroPtr = std::make_unique<Tetromino>(tetrominoFactory.GetRandomTetromino(previewTetroSpawnPosition));
		previewTetroPtr->Draw();

		if (IsColliding(currentTetroPtr->GetState().GetTranslatedBlocks()))
		{
			auto & stManager = StateManager::GetInstance();
			stManager.PopState();
			stManager.PushState(std::make_unique<GameOverState>());
			return;
		}
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
		previewTetroSpawnPosition({_position.X + _size.X + 3, _position.Y + 4}),
		tetrominoFactory(73816),
		previewTetroPtr(nullptr),
		currentTetroPtr(nullptr),
		elapsedTime(0),
		score(0)
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

		DrawScore();
	}
}
