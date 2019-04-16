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
		unsigned score;

		void DrawScore() const;

		bool IsBlockOutOfBounds(COORD const& block) const;
		bool IsColliding(std::vector<COORD> const & blockPositions) const;

		bool IsRowFull(SHORT const row) const;
		void PopRow(SHORT const row);
		void PopFullRows(SHORT const startRow, SHORT const endRow);
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

