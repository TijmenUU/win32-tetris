#pragma once
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
		Tetromino GetTetromino(TetrominoType const type, COORD const& spawnPosition);
		Tetromino GetRandomTetromino(COORD const& spawnPosition);

		TetrominoFactory(int const seed);
	};
}
