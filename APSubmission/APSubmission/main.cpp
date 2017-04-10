#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <Windows.h>
#include <algorithm>
#include <time.h>

#include "Game.h"

#define wait(x) Sleep(x * 1000)
#define BUFF_SIZE 120

Game *game;

int main()
{
	char buf[BUFF_SIZE];
	setvbuf(stdout, buf, _IOFBF, BUFF_SIZE);
	SetConsoleTitle(L"APSubmission");
	game = new Game();
	game->AddWallCharacters({ '+', '@', '=' });
	game->de->DrawBox('+', 5, 5, 20, 20, 1);
	game->SpawnPlayer('#', 10, 10);
	while (true) {
		if (GetAsyncKeyState(VK_ESCAPE))
			break;
		else if (GetAsyncKeyState(0x57/*W*/) || GetAsyncKeyState(VK_UP))
			game->MovePlayerUp();
		else if (GetAsyncKeyState(0x53/*S*/) || GetAsyncKeyState(VK_DOWN))
			game->MovePlayerDown();
		else if (GetAsyncKeyState(0x41/*A*/) || GetAsyncKeyState(VK_LEFT))
			game->MovePlayerLeft();
		else if (GetAsyncKeyState(0x44/*D*/) || GetAsyncKeyState(VK_RIGHT))
			game->MovePlayerRight();
		game->de->Draw();
		wait(0.2);
	}
	FreeConsole();
	return 0;
}