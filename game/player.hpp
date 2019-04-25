#pragma once
#include "field.hpp"
#include <memory>
#include "tetrominofactory.hpp"

namespace Game
{
	class Player
	{
	private:
		COORD const spawnPosition;
		COORD const previewSpawnPosition;
		COORD const scorePosition;
		Field& field;

		TetrominoFactory tetrominoFactory;
		std::unique_ptr<Tetromino> previewTetroPtr, currentTetroPtr;

		unsigned autoDropElapsedTime; // in milliseconds
		unsigned score;

		void DrawScore() const;
		void CalculateScore(unsigned const rowsPopped);

		void ClearPreviewArea() const;

		void CycleTetromino();
		bool HandleInput();

	public:
		void Update(unsigned const elapsedMs);

		Player(COORD const _previewSpawnPosition,
			COORD const _scorePosition,
			Field& _field);
	};
}
