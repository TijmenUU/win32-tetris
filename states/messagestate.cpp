#include "../conutils/cursor.hpp"
#include "messagestate.hpp"

void MessageState::DrawMessage(std::string msg, Color::Color const& color) const
{
	if (msg.size() > maxLineLength)
	{
		msg.resize(static_cast<unsigned>(maxLineLength));
	}

	SHORT const x = (maxLineLength / 2) - (msg.size() / 2) + lineStartPosition.X;
	Color::Set(color);
	Cursor::Set({ lineStartPosition.X, lineStartPosition.Y });
	for (SHORT i = lineStartPosition.X; i < x; ++i)
		std::cout << ' ';
	std::cout << msg;
	for (SHORT i = x + msg.size(); i < lineStartPosition.X + maxLineLength; ++i)
		std::cout << ' ';
}

void MessageState::Awake()
{
	// chirp chirp
}

MessageState::MessageState(COORD const _lineStartPosition,
	SHORT const _maxLineLength,
	std::string const& message,
	Color::Color const& color)
	: lineStartPosition(_lineStartPosition),
	maxLineLength(_maxLineLength)
{
	DrawMessage(message, color);
}

MessageState::~MessageState()
{
}
