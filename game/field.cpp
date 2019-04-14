#include "../conutils/color.hpp"
#include "../conutils/coordops.hpp"
#include "../conutils/cursor.hpp"
#include "../eventhandler.hpp"
#include <cassert>
#include "field.hpp"

namespace Game
{
	void Field::HandleInput()
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

		if (evHandler.WasActionReleased(PlayerActions::MoveDown))
		{
			currentTetroPtr->MoveDown();
		}
		
		if (evHandler.WasActionReleased(PlayerActions::MoveLeft))
		{
			currentTetroPtr->MoveLeft();
		}
		else if (evHandler.WasActionReleased(PlayerActions::MoveRight))
		{
			currentTetroPtr->MoveRight();
		}

		// DEBUG KEYS BELOW
		if (evHandler.WasActionReleased(PlayerActions::Yes))
		{
			COORD const spawnPosition{ position.X + size.X / 2, position.Y };
			currentTetroPtr = std::make_unique<Tetromino>(tetrominoFactory.GetRandomTetromino(spawnPosition));
		}
	}

	void Field::Update(unsigned const elapsedMs)
	{
		HandleInput();
	}

	void Field::Draw() const
	{
		for (SHORT y = position.Y; y < position.Y + size.Y; ++y)
		{
			Cursor::Set(COORD{ position.X, y });
			Color::Set(Color::Color()); // Black and white
			for (SHORT x = position.X; x < position.X + size.X; ++x)
			{
				std::cout << ' ';
			}
		}

		if (currentTetroPtr != nullptr)
		{
			currentTetroPtr->Draw();
		}
	}

	Field::Field(COORD _position, COORD _size)
		: position(_position),
		size(_size),
		tetrominoFactory(73816),
		previewTetroPtr(nullptr),
		currentTetroPtr(nullptr)
	{
		COORD const spawnPosition{ position.X + size.X / 2, position.Y };
		currentTetroPtr = std::make_unique<Tetromino>(tetrominoFactory.GetRandomTetromino(spawnPosition));
	}
}
