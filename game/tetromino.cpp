#include "../conutils/coordops.hpp"
#include "../conutils/cursor.hpp"
#include "tetromino.hpp"

namespace Game
{
	std::vector<COORD> TetrominoState::GetTranslatedBlocks() const
	{
		std::vector<COORD> retval = blocks;
		for (auto& c : retval)
		{
			c = position + c;
		}

		return retval;
	}

	void TetrominoState::Draw(Color::Color const& color, char const character) const
	{
		auto const blocksToDraw = GetTranslatedBlocks();
		Color::Set(color);
		for (auto const& c : blocksToDraw)
		{
			Cursor::Set(c);
			std::cout << character;
		}
	}

	bool TetrominoState::operator==(TetrominoState const& other) const
	{
		if (other.position.X != position.X || other.position.Y != position.Y)
			return false;

		if (other.blocks.size() != blocks.size())
			return false;

		for (unsigned i = 0; i < blocks.size(); ++i)
		{
			if (other.blocks[i].X != blocks[i].X || other.blocks[i].Y != blocks[i].Y)
				return false;
		}

		return true;
	}

	bool TetrominoState::operator!=(TetrominoState const& other) const
	{
		return !operator==(other);
	}

	void Tetromino::RotateRight()
	{
		for (auto& c : state.blocks)
		{
			SHORT const oldY = c.Y;
			c.Y = c.X;
			c.X = -oldY;
		}
	}

	void Tetromino::RotateLeft()
	{
		for (auto& c : state.blocks)
		{
			SHORT const oldY = c.Y;
			c.Y = -c.X;
			c.X = oldY;
		}
	}

	void Tetromino::Move(SHORT const X_displacement)
	{
		state.position.X += X_displacement;
	}

	void Tetromino::SetPosition(COORD const& _position)
	{
		state.position = _position;
	}

	void Tetromino::SetState(TetrominoState const& _state)
	{
		state = _state;
	}

	TetrominoState const& Tetromino::GetState() const
	{
		return state;
	}

	Color::Color const& Tetromino::GetColor() const
	{
		return color;
	}

	char Tetromino::GetCharacter() const
	{
		return character;
	}

	void Tetromino::Draw() const
	{
		state.Draw(color, character);
	}

	Tetromino::Tetromino(TetrominoType const _type,
		COORD _position,
		char const _character,
		Color::Color const _color)
		: type(_type),
		character(_character),
		color(_color)
	{
		state.position = _position;
	}

	Tetromino Tetromino::CreateBar(COORD const _position)
	{
		auto t = Tetromino(
			TetrominoType::Bar,
			_position,
			'=',
			Color::Color(Color::Foreground::CYAN, Color::Background::DARKCYAN)
		);

		t.state.blocks.push_back(COORD{ 0, 0 });
		t.state.blocks.push_back(COORD{ 0, 1 });
		t.state.blocks.push_back(COORD{ 0, 2 });
		t.state.blocks.push_back(COORD{ 0, 3 });

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

		t.state.blocks.push_back(COORD{ 0, 0 });
		t.state.blocks.push_back(COORD{ 0, 1 });
		t.state.blocks.push_back(COORD{ 1, 0 });
		t.state.blocks.push_back(COORD{ 1, 1 });

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

		t.state.blocks.push_back(COORD{ 0, 0 });
		t.state.blocks.push_back(COORD{ 0, 1 });
		t.state.blocks.push_back(COORD{ 0, 2 });
		t.state.blocks.push_back(COORD{ 1, 2 });

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

		t.state.blocks.push_back(COORD{ 0, 0 });
		t.state.blocks.push_back(COORD{ 0, 1 });
		t.state.blocks.push_back(COORD{ 1, 1 });
		t.state.blocks.push_back(COORD{ 1, 2 });

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

		t.state.blocks.push_back(COORD{ 0, 0 });
		t.state.blocks.push_back(COORD{ 1, 0 });
		t.state.blocks.push_back(COORD{ 2, 0 });
		t.state.blocks.push_back(COORD{ 1, 1 });

		return t;
	}
}