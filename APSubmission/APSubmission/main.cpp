#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <Windows.h>
#include <algorithm>
#include <time.h>

#include "DrawEngine.h"
#include "Game.h"

#define wait(x) Sleep(x * 1000)

DrawEngine *de;
Game game;

int main()
{
	char buf[120];
	setvbuf(stdout, buf, _IOFBF, 120);
	SetConsoleTitle(L"APSubmission");
	de = new DrawEngine();
	de->DrawBox('+', 5, 5, 20, 20, 1);
	game.SpawnPlayer('#', 10, 10);
	while (true) {
		if (GetAsyncKeyState(VK_ESCAPE))
			break;
		else if (GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP))
			game.MovePlayerUp();
		else if (GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN))
			game.MovePlayerDown();
		else if (GetAsyncKeyState(0x41) || GetAsyncKeyState(VK_LEFT))
			game.MovePlayerLeft();
		else if (GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_RIGHT))
			game.MovePlayerRight();
		de->Draw();
		wait(0.2);
	}
	return 0;
}