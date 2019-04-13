#pragma once
#include "eventhandler.hpp"
#include "statemanager.hpp"

class Core
{
public:
	void Run(unsigned const targetFrameTime);

	Core();
	~Core();
};

