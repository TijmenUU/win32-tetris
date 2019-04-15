#pragma once
#include <memory>
#include "tetrominofactory.hpp"
#include <Windows.h>

namespace Game
{
	class Field
	{
	private:
		COORD const position;
		COORD const size;
		COORD const tetroSpawnPosition;
		COORD const previewTetroSpawnPosition;
		std::vector<bool> occupiedBlocks;
		TetrominoFactory tetrominoFactory;
		std::unique_ptr<Tetromino> previewTetroPtr, currentTetroPtr;
		unsigned elapsedTime; // in milliseconds

		bool IsColliding(std::vector<COORD> const & blockPositions) const;
		void Merge(std::vector<COORD> const& blockPositions);

		void SpawnTetromino();

		// Returns whether the player wants to move down
		bool HandleInput();

	public:
		void Update(unsigned const elapsedMs);

		// TODO track tetromino blocks
		// TODO add tetris row popping logic

		Field(COORD _position, COORD _size);
	};
}

