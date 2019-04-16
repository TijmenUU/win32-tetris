/*
	Do yourself a favour and try not to include this in other
	header files. Thanks!
*/
#pragma once
#include <windows.h>

namespace Config
{
	static COORD const consoleBufferSize{ 25, 30 }; // in characters
	static COORD const windowSize{ 350, 525 };

	static COORD const playingFieldPosition{ 1, 1 };
	static COORD const playingFieldSize{ 28, 28 };
	static COORD const scorePosition{ playingFieldPosition.X + playingFieldSize.X + 2, 2 };
}