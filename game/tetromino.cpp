#include "../conutils/coordops.hpp"
#include "../conutils/cursor.hpp"
#include "tetromino.hpp"

namespace Game
{
	void Tetromino::RotateRight()
	{
		for (auto& c : blocks)
		{
			SHORT const oldY = c.Y;
			c.Y = c.X;
			c.X = -oldY;
		}
	}

	void Tetromino::RotateLeft()
	{
		for (auto& c : blocks)
		{
			SHORT const oldY = c.Y;
			c.Y = -c.X;
			c.X = oldY;
		}
	}

	void Tetromino::MoveDown()
	{
		++position.Y;
	}

	void Tetromino::MoveLeft()
	{
		--position.X;
	}

	void Tetromino::MoveRight()
	{
		++position.X;
	}

	void Tetromino::SetPosition(COORD const& _position)
	{
		position = _position;
	}

	std::vector<COORD> Tetromino::GetBlockPositions() const
	{
		std::vector<COORD> retval = blocks;
		for (auto & c : retval)
		{
			c = position + c;
		}

		return retval;
	}

	void Tetromino::Draw() const
	{
		auto const blocksToDraw = GetBlockPositions();
		Color::Set(color);
		for (auto const& c : blocksToDraw)
		{
			Cursor::Set(c);
			std::cout << character;
		}
	}

	Tetromino::Tetromino(TetrominoType const _type,
		COORD _position,
		char const _character,
		Color::Color const _color)
		: type(_type),
		position(_position),
		character(_character),
		color(_color)
	{
	}

	Tetromino Tetromino::CreateBar(COORD const _position)
	{
		auto t = Tetromino(
			TetrominoType::Bar,
			_position,
			'=',
			Color::Color(Color::Foreground::CYAN, Color::Background::DARKCYAN)
		);

		t.blocks.push_back(COORD{ 0, 0 });
		t.blocks.push_back(COORD{ 0, 1 });
		t.blocks.push_back(COORD{ 0, 2 });
		t.blocks.push_back(COORD{ 0, 3 });

		return t;
	}

	Tetromino Tetromino::CreateBlock(COORD const _position)
	{
		auto t = Tetromino(
			TetrominoType::Block,
			_position,
			'O',
			Color::Color(Color::Foreground::YELLOW, Color::Background::DARKYELLOW)
		);

		t.blocks.push_back(COORD{ 0, 0 });
		t.blocks.push_back(COORD{ 0, 1 });
		t.blocks.push_back(COORD{ 1, 0 });
		t.blocks.push_back(COORD{ 1, 1 });

		return t;
	}

	Tetromino Tetromino::CreateL(COORD const _position)
	{
		auto t = Tetromino(
			TetrominoType::L,
			_position,
			'L',
			Color::Color(Color::Foreground::RED, Color::Background::DARKRED)
		);

		t.blocks.push_back(COORD{ 0, 0 });
		t.blocks.push_back(COORD{ 0, 1 });
		t.blocks.push_back(COORD{ 0, 2 });
		t.blocks.push_back(COORD{ 1, 2 });

		return t;
	}

	Tetromino Tetromino::CreateZ(COORD const _position)
	{
		auto t = Tetromino(
			TetrominoType::Z,
			_position,
			'Z',
			Color::Color(Color::Foreground::GREEN, Color::Background::DARKGREEN)
		);

		t.blocks.push_back(COORD{ 0, 0 });
		t.blocks.push_back(COORD{ 0, 1 });
		t.blocks.push_back(COORD{ 1, 1 });
		t.blocks.push_back(COORD{ 1, 2 });

		return t;
	}

	Tetromino Tetromino::CreateTriangle(COORD const _position)
	{
		auto t = Tetromino(
			TetrominoType::Triangle,
			_position,
			'=',
			Color::Color(Color::Foreground::PURPLE, Color::Background::DARKPURPLE)
		);

		t.blocks.push_back(COORD{ 0, 0 });
		t.blocks.push_back(COORD{ 1, 0 });
		t.blocks.push_back(COORD{ 2, 0 });
		t.blocks.push_back(COORD{ 1, 1 });

		return t;
	}
}