#pragma once
#include <Windows.h>

class PlayingField
{
private:
	COORD const topLeft;
	COORD const size;

public:
	PlayingField();
	~PlayingField();
};

