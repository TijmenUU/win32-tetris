#pragma once
#include "MessageState.hpp"

class GameOverState : public MessageState
{
public:
	void Update(unsigned const elapsedMs) override;

	GameOverState();
	~GameOverState();
};
