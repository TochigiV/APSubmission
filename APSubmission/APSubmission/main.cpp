#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <Windows.h>
#include <algorithm>
#include <time.h>

#include "Game.h"

#define wait(x) Sleep(x * 1000)
#define BUFF_SIZE 512

Game *game;

/*TODO LIST:
	[*] Random map generation
	[*] Enemy AI
*/

int totalgold;

void generateGold()
{
	srand(time(nullptr));
	int ammount = rand() % 101;
	for (totalgold = 0; totalgold < ammount; totalgold++)
	{
		int x = rand() % (game->de->GetColumns() - 2);
		int y = rand() % (game->de->GetRows() - 2);
		x += 2; y += 2;
		char a = game->de->GetChar(x, y);
		if (a != '+' && a != '@' && a != '&')
			game->de->DrawSinglePixel('#', x, y);
		else totalgold--;
	}
}

int main()
{
	setvbuf(stdout, NULL, _IOFBF, BUFF_SIZE);
	SetConsoleTitle(L"APSubmission");
	game = new Game('@', 10, 10); //new game instance, spawn player (@) at x: 10 y: 10
	game->SetWallCharacter('+'); //sets the character that will act as a wall

	game->de->FillScreen(' ');
	game->de->DrawTextA("+ = wall", 20, 11);
	game->de->DrawTextA("@ = player", 20, 12);
	game->de->DrawTextA("& = enemy", 20, 13);
	game->de->DrawTextA("# = gold coin", 20, 14);
	game->de->DrawTextA("W, A, S, D, Up Arrow, Down Arrow, Left Arrow, Right Arrow = movement", 20, 15);
	game->de->DrawTextA("Press Enter to continue (or Esc to exit)", 20, 16);
	game->de->Draw();
	wait(0.1);
	while (true) if (GetAsyncKeyState(VK_RETURN)) break; else if (GetAsyncKeyState(VK_ESCAPE)) exit(0);
	game->de->FillScreen(' ');
	
	game->de->DrawSinglePixel('@', game->GetPlayerX(), game->GetPlayerY());
	game->de->DrawBox('+', 5, 5, 20, 20, 1);
	game->de->DrawRect(' ', 24, 10, 1, 10);

	game->de->DrawRect('+', 0, 1, 11, 1);
	game->de->DrawRect('+', 10, 0, 1, 1);
	
	generateGold();

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

		if (game->score > 9999) game->score = 9999;
		if (game->score == totalgold)
		{
			if (MessageBox(NULL, L"You got all of the gold! Play again?", L"Congrats!", MB_YESNO) == IDYES)
			{
				game->score = 0;
				totalgold = 0;
				generateGold();
			}
			else break;
		}
		std::string scstr = "Gold: " + std::to_string(game->score);
		game->de->DrawTextA(scstr.c_str(), 0, 0);
		game->de->Draw(); //re-draw the scene
		wait(0.1); 
	}
	delete game;
	return 0;
}
