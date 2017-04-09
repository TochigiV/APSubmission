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

#define BUFF_SIZE 119

int main()
{
	char buf[BUFF_SIZE];
	setvbuf(stdout, buf, _IOFBF, BUFF_SIZE);
	SetConsoleTitle(L"APSubmission");
	de = new DrawEngine();
	de->DrawBox('+', 5, 5, 20, 20, 1);
	game.SpawnPlayer('#', 10, 10);
	while (true) {
		if (GetAsyncKeyState(VK_ESCAPE))
			break;
		else if (GetAsyncKeyState(0x57/*W*/) || GetAsyncKeyState(VK_UP))
			game.MovePlayerUp();
		else if (GetAsyncKeyState(0x53/*S*/) || GetAsyncKeyState(VK_DOWN))
			game.MovePlayerDown();
		else if (GetAsyncKeyState(0x41/*A*/) || GetAsyncKeyState(VK_LEFT))
			game.MovePlayerLeft();
		else if (GetAsyncKeyState(0x44/*D*/) || GetAsyncKeyState(VK_RIGHT))
			game.MovePlayerRight();
		de->Draw();
		wait(0.2);
	}
	FreeConsole();
	return 0;
}