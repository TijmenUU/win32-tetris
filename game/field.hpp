#pragma once
#include <memory>
#include "tetrominofactory.hpp"
#include <Windows.h>

namespace Game
{
	class Field
	{
	private:
		COORD position;
		COORD size;
		TetrominoFactory tetrominoFactory;
		std::unique_ptr<Tetromino> previewTetroPtr, currentTetroPtr;

		void HandleInput();

	public:
		void Update(unsigned const elapsedMs);
		// TODO Only refresh when changes happened
		// TODO Refresh only changed lines
		// TODO Allow outside line refresh trigger (to repaint area altered by pause text)
		// TODO track tetromino blocks
		// TODO add tetris row popping logic
		void Draw() const;

		Field(COORD _position, COORD _size);
	};
}

