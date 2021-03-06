#include "../conutils/color.hpp"
#include "../conutils/coordops.hpp"
#include "../conutils/cursor.hpp"
#include "../userinput.hpp"
#include <cstdio>
#include "field.hpp"

namespace Entity
{
	bool Field::IsBlockOutOfBounds(COORD const& block) const
	{
		return block.X < position.X || block.X >= (position.X + size.X) || block.Y < position.Y || block.Y >= (position.Y + size.Y);
	}

	bool Field::IsRowFull(SHORT const row) const
	{
		SHORT const start = row * size.X;
		for (SHORT i = start; i < start + size.X; ++i)
		{
			if (!occupiedBlocks[i])
				return false;
		}

		return true;
	}

	void Field::PopRow(SHORT const row)
	{
		// Clear row
		Cursor::Set(COORD{ position.X, row + position.Y });
		Color::Set(Color::Color());
		for (SHORT x = 0; x < size.X; ++x)
		{
			std::cout << ' ';
			occupiedBlocks[x + (row * size.X)] = false;
		}

		// Shift everything down
		if (row > 0)
		{
			// Correct the visuals
			std::vector<CHAR_INFO> blocks;
			blocks.resize(size.X * row);

			SMALL_RECT region;
			region.Top = position.Y;
			region.Left = position.X;
			region.Bottom = position.Y + row;
			region.Right = region.Left + size.X;

			COORD const bufferSize{ size.X, row };

			ReadConsoleOutput(
				GetStdHandle(STD_OUTPUT_HANDLE),
				&blocks[0],
				bufferSize,
				COORD{ 0, 0 },
				&region
			);

			++region.Top;
			++region.Bottom;
			WriteConsoleOutput(
				GetStdHandle(STD_OUTPUT_HANDLE),
				&blocks[0],
				bufferSize,
				COORD{ 0, 0 },
				&region
			);

			// Update occupiedBlocks
			for (SHORT i = (size.X - 1) + row * size.X; i >= size.X; --i)
			{
				occupiedBlocks[i] = occupiedBlocks[i - size.X];
			}
		}

		// Clear the top row
		Color::Set(Color::Color());
		Cursor::Set(position);
		for (SHORT x = 0; x < size.X; ++x)
		{
			occupiedBlocks[x] = false;
			std::cout << ' ';
		}
	}

	unsigned Field::PopFullRows(SHORT const startRow, SHORT const endRow)
	{
		unsigned rowsPopped = 0;
		for (SHORT y = startRow; y <= endRow; ++y)
		{
			if (IsRowFull(y))
			{
				PopRow(y);
				++rowsPopped;
				--y;
			}
		}

		return rowsPopped;
	}

	unsigned Field::Merge(std::vector<COORD> const& blockPositions)
	{
		SHORT minY = size.Y, maxY = 0;
		for (auto const& b : blockPositions)
		{
			if (IsBlockOutOfBounds(b))
				continue;

			if (minY > b.Y)
				minY = b.Y;
			if (maxY < b.Y)
				maxY = b.Y;

			unsigned const index = (b.X - position.X) + (b.Y - position.Y) * size.X;
			occupiedBlocks[index] = true;
		}

		return PopFullRows(minY - position.Y, maxY - position.Y);
	}

	bool Field::IsColliding(std::vector<COORD> const& blockPositions) const
	{
		for (auto const& b : blockPositions)
		{
			if (IsBlockOutOfBounds(b))
				return true;

			unsigned const index = (b.X - position.X) + (b.Y - position.Y) * size.X;
			if (occupiedBlocks[index])
			{
				return true;
			}
		}

		return false;
	}

	COORD const& Field::GetPosition() const
	{
		return position;
	}

	COORD const& Field::GetSize() const
	{
		return size;
	}

	Field::Field(COORD _position, COORD _size)
		: position(_position),
		size(_size)
	{
		occupiedBlocks.resize(_size.X * _size.Y);

		Color::Set(Color::Color()); // Black and white

		// Clear the field
		for (SHORT y = position.Y; y < position.Y + size.Y; ++y)
		{
			Cursor::Set(COORD{ position.X, y });
			for (SHORT x = position.X; x < position.X + size.X; ++x)
			{
				std::cout << ' ';
			}
		}
	}
}
