#pragma once
#include "messagestate.hpp"

class WindowSizeState : public MessageState
{
private:
	COORD const minWindowSize;

public:
	void Update(unsigned const elapsedMs) override;

	WindowSizeState(COORD const _lineStartPosition,
		SHORT const _maxLineLength,
		COORD const _minWindowSize);
	~WindowSizeState();
};

