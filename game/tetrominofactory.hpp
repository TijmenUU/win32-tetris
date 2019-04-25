#pragma once
#include <memory>
#include <random>
#include "tetromino.hpp"

namespace Game
{
	class TetrominoFactory
	{
	private:
		std::default_random_engine eng;
		std::uniform_int_distribution<int> dist;
		std::vector<Tetromino> tetrominos;

	public:
		std::unique_ptr<Tetromino> GetTetromino(TetrominoType const type, COORD const& spawnPosition);
		std::unique_ptr<Tetromino> GetRandomTetromino(COORD const& spawnPosition);

		TetrominoFactory(int const seed);
	};
}
