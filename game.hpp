#pragma once
#include "eventhandler.hpp"
#include "statemanager.hpp"

class Game
{
public:
	void Run(unsigned const targetFrameTime);

	Game();
	~Game();
};

