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

	struct TetrominoState
	{
		COORD position;
		std::vector<COORD> blocks;

		std::vector<COORD> GetTranslatedBlocks() const;
		void Draw(Color::Color const & color, char const character) const;

		bool operator==(TetrominoState const& other) const;
		bool operator!=(TetrominoState const& other) const;
	};

	class Tetromino
	{
	private:
		TetrominoType const type;
		char const character;
		Color::Color const color;
		TetrominoState state;

		Tetromino(TetrominoType const _type,
			COORD _position,
			char const _character,
			Color::Color const _color);

	public:
		void RotateRight();
		void RotateLeft();

		void Move(SHORT const X_displacement);

		void SetPosition(COORD const& _position);
		void SetState(TetrominoState const& _state);

		TetrominoState const & GetState() const;
		Color::Color const& GetColor() const;
		char GetCharacter() const;

		void Draw() const;

		static Tetromino CreateBar(COORD const _position);
		static Tetromino CreateBlock(COORD const _position);
		static Tetromino CreateL(COORD const _position);
		static Tetromino CreateZ(COORD const _position);
		static Tetromino CreateTriangle(COORD const _position);
	};
}


