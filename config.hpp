#pragma once
#include <windows.h>

namespace Config
{
	static COORD const consoleBufferSize{ 40, 30 }; // in characters
	static COORD const windowSize{ 600, 525 };

	static COORD const playingFieldPosition{ 1, 1 };
	static COORD const playingFieldSize{ 28, 28 };
	static COORD const scorePosition{ playingFieldPosition.X + playingFieldSize.X + 2, 2 };
}