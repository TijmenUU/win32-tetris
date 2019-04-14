#include "tetrominofactory.hpp"

namespace Game
{
	Tetromino TetrominoFactory::GetTetromino(TetrominoType const type, COORD const& spawnPosition)
	{
		switch (type)
		{
		case TetrominoType::Bar:
			return Tetromino::CreateBar(spawnPosition);

		case TetrominoType::Block:
			return Tetromino::CreateBlock(spawnPosition);

		case TetrominoType::L:
			return Tetromino::CreateL(spawnPosition);

		case TetrominoType::Z:
			return Tetromino::CreateZ(spawnPosition);

		case TetrominoType::Triangle:
		default:
			return Tetromino::CreateTriangle(spawnPosition);
		}
	}

	Tetromino TetrominoFactory::GetRandomTetromino(COORD const& spawnPosition)
	{
		TetrominoType const type = static_cast<TetrominoType>(dist(eng));
		return GetTetromino(type, spawnPosition);
	}

	TetrominoFactory::TetrominoFactory(int const seed)
		: eng(seed),
		dist(0, static_cast<int>(TetrominoType::COUNT) - 1)
	{
	}

}