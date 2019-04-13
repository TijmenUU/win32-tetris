#pragma once
#include "basestate.hpp"
#include "../conutils/color.hpp"
#include <string>
#include <Windows.h>

class MessageState : public State
{
protected:
	COORD const lineStartPosition;
	SHORT const maxLineLength;

	void DrawMessage(std::string msg, Color::Color const& color) const;

public:
	void Awake() override;

	MessageState(COORD const _lineStartPosition,
		SHORT const _maxLineLength,
		std::string const & message,
		Color::Color const & color);
	~MessageState();
};

