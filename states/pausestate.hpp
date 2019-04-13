#pragma once
#include "messagestate.hpp"

class PauseState : public MessageState
{
public:
	void Update(unsigned const elapsedMs) override;

	PauseState(COORD const _lineStartPosition,
		SHORT const _maxLineLength);
	~PauseState();
};

