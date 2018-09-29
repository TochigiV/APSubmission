/*
MIT License

Copyright (c) 2017 Tochigi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Game.h"

#define wait(x) Sleep((DWORD)(x * 1000))
#define pause() fputs("Press any key to continue . . . ", stdout); _getch(); fputc('\n', stdout);

#define USE_ASYNC 1 //set to 0 if you want to use GetKeyState instead of GetAsyncKeyState
#if USE_ASYNC
	#define GetKey(vkey) (GetAsyncKeyState(vkey) >> 15) //If vkey is down, the high bit is 1
#else
	#define GetKey(vkey) (GetKeyState(vkey) >> 15) //If vkey is down, the high bit is 1
#endif

Game* game;
DrawEngine* drawEngine;

int totalGold;

void generateGold()

{
	srand((unsigned int)time(nullptr));
	int ammount = rand() % 51;
	for (totalGold = 0; totalGold != ammount; totalGold++)
	{
		int x = rand() % (drawEngine->GetColumns() - 2);
		int y = rand() % (drawEngine->GetRows() - 2);
		x += 2; y += 2;
		wchar_t a = drawEngine->GetChar(x, y);
		if (a != TEXT('+') && a != TEXT('@') && a != TEXT('&'))
			drawEngine->DrawSinglePixel(TEXT('#'), x, y);
		else totalGold--;
	}
}

bool multiplayer = false;

int main()
{
	HWND consoleWindow = GetConsoleWindow();
	SetConsoleTitle(TEXT("APSubmission"));
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	try
	{
		game = new Game(TEXT('@'), 10, 10); //new game instance, spawn player (@) at x: 10 y: 10
		game->SetWallCharacter(TEXT('+')); //sets the character that will act as a wall
		drawEngine = game->drawEngine;	

		drawEngine->FillScreen(TEXT(' '));
		drawEngine->PutText(TEXT("+ = wall"), 20, 11);
		drawEngine->PutText(TEXT("@ = player"), 20, 12);
		drawEngine->PutText(TEXT("# = gold coin"), 20, 13);
		drawEngine->PutText(TEXT("W, A, S, D, Up Arrow, Down Arrow, Left Arrow, Right Arrow = movement"), 20, 14);
		drawEngine->PutText(TEXT("Press Enter to continue (or Esc to exit)"), 20, 15);
		drawEngine->Draw();
		wait(0.1);
		while (true) {
			if (consoleWindow == GetForegroundWindow())
			{
				if (GetKey(VK_RETURN))
					break;
				else if (GetKey(VK_ESCAPE))
					goto end;
			}
		}
		drawEngine->FillScreen(TEXT(' '));
	
		drawEngine->DrawSinglePixel(TEXT('@'), game->GetPlayerX(), game->GetPlayerY());
	
		drawEngine->DrawLine(TEXT('+'), 0, 1, 11, 1);
		drawEngine->DrawLine(TEXT('+'), 10, 0, 1, 1);
	
		generateGold();
	
		while (true) {
			if (consoleWindow == GetForegroundWindow())
			{
				if (GetKey(VK_ESCAPE))
					break;
				else if (GetKey(0x57/*W*/) || GetKey(VK_UP))
					game->MovePlayerUp();
				else if (GetKey(0x41/*A*/) || GetKey(VK_LEFT))
					game->MovePlayerLeft();
				else if (GetKey(0x53/*S*/) || GetKey(VK_DOWN))
					game->MovePlayerDown();
				else if (GetKey(0x44/*D*/) || GetKey(VK_RIGHT))
					game->MovePlayerRight();
			}
	
			if (game->score > 9999) game->score = 9999;
			if (game->score == totalGold)
			{
				if (MessageBox(NULL, TEXT("You got all of the gold! Play again?"), TEXT("Congrats!"), MB_YESNO) == IDYES)
				{
					game->score = 0;
					totalGold = 0;
					drawEngine->DrawLine(' ', 0, 0, 10, 1);
					generateGold();
				}
				else break;
			}
			std::wstring scoreString = TEXT("Gold: ") + std::to_wstring(game->score);
			drawEngine->PutText(scoreString.c_str(), 0, 0);
			drawEngine->Draw();
		}
	}
	catch (std::wstring exceptionMessage)
	{
		MessageBox(consoleWindow, exceptionMessage.c_str(), TEXT("Error"), MB_OK | MB_ICONERROR);
	}
	end:
	delete game; //if it exists (which it should)
	return 0;
}
