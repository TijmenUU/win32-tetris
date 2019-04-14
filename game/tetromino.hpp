#pragma once
#include "../conutils/color.hpp"
#include <vector>
#include <Windows.h>

namespace Game
{
	enum class TetrominoType
	{
		Bar = 0,
		Block,
		L,
		Z,
		Triangle,
		COUNT
	};

	class Tetromino
	{
	private:
		TetrominoType const type;
		COORD position;
		const char character;
		Color::Color color;
		std::vector<COORD> blocks;

		Tetromino(TetrominoType const _type,
			COORD _position,
			char const _character,
			Color::Color const _color);

	public:
		void RotateRight();
		void RotateLeft();

		void MoveDown();
		void MoveLeft();
		void MoveRight();

		void SetPosition(COORD const& _position);

		std::vector<COORD> GetBlockPositions() const;

		void Draw() const;

		static Tetromino CreateBar(COORD const _position);
		static Tetromino CreateBlock(COORD const _position);
		static Tetromino CreateL(COORD const _position);
		static Tetromino CreateZ(COORD const _position);
		static Tetromino CreateTriangle(COORD const _position);
	};
}


