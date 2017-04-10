#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <Windows.h>
#include <algorithm>
#include <time.h>

#include "Game.h"

#define wait(x) Sleep(x * 1000)
#define BUFF_SIZE 50

Game *game;

/*TODO LIST:
	[*] Random map generation
	[*] Enemy AI
	[*] Scoring
*/

int main()
{
	setvbuf(stdout, NULL, _IOFBF, BUFF_SIZE);
	SetConsoleTitle(L"APSubmission");
	game = new Game('@', 10, 10); //new game instance, spawn player (@) at x: 10 y: 10
	game->SetWallCharacter('+'); //sets the character that will act as a wall
	game->de->DrawBox('+', 5, 5, 20, 20, 1);
	game->de->DrawRect(' ', 24, 10, 1, 10);
	while (true) {
		if (GetAsyncKeyState(VK_ESCAPE))
			break;
		else if (GetAsyncKeyState(0x57/*W*/) || GetAsyncKeyState(VK_UP))
			game->MovePlayerUp();
		else if (GetAsyncKeyState(0x41/*A*/) || GetAsyncKeyState(VK_LEFT))
			game->MovePlayerLeft();
		else if (GetAsyncKeyState(0x53/*S*/) || GetAsyncKeyState(VK_DOWN))
			game->MovePlayerDown();
		else if (GetAsyncKeyState(0x44/*D*/) || GetAsyncKeyState(VK_RIGHT))
			game->MovePlayerRight();
		game->de->Draw(); //re-draw the scene
		wait(0.1); 
	}
	FreeConsole();
	return 0;
}