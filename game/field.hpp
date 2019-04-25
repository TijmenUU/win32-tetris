#pragma once
#include <Windows.h>

namespace Game
{
	class Field
	{
	private:
		COORD const position;
		COORD const size;

		std::vector<bool> occupiedBlocks;

		bool IsBlockOutOfBounds(COORD const& block) const;
		bool IsRowFull(SHORT const row) const;
		void PopRow(SHORT const row);
		unsigned PopFullRows(SHORT const startRow, SHORT const endRow);

	public:
		unsigned Merge(std::vector<COORD> const& blockPositions);
		bool IsColliding(std::vector<COORD> const& blockPositions) const;

		COORD const& GetPosition() const;
		COORD const& GetSize() const;

		Field(COORD _position, COORD _size);
	};
}

