#pragma once
#include "userinput.hpp"
#include "statestack.hpp"

class Game
{
public:
	void Run(unsigned const targetFrameTime);

	Game();
	~Game();
};

