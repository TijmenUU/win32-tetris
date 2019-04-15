#pragma once
#include "messagestate.hpp"

class PauseState : public MessageState
{
public:
	void Update(unsigned const elapsedMs) override;

	PauseState();
	~PauseState();
};

