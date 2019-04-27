#pragma once
#include <windows.h>

// Static constant variables _only_ 
namespace Config
{
	static COORD const consoleBufferSize{ 25, 30 }; // in characters
	static COORD const windowSize{ 350, 525 };

	static COORD const playingFieldPosition{ 1, 1 };
	static COORD const playingFieldSize{ 28, 28 };
	static COORD const scorePosition{ playingFieldPosition.X + playingFieldSize.X + 2, 2 };
	static COORD const previewTetrominoPosition{ scorePosition.X, scorePosition.Y + 3 };
	static COORD const controlsPosition{ scorePosition.X, previewTetrominoPosition.Y + 5 };
}