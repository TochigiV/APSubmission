/*
MIT License

Copyright (c) 2020 Bailey Brownie

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

#include <ctime>

#define WAIT(x) Sleep(static_cast<DWORD>(x * 1000))
#define PAUSE() fputs("Press any key to continue . . . ", stdout); _getch(); fputc('\n', stdout);

#define USE_ASYNC 1 //set to 0 if you want to use GetKeyState instead of GetAsyncKeyState
#if USE_ASYNC
	#define GETKEY(vkey) (GetAsyncKeyState(vkey) >> 15) //If vkey is down, the high bit is 1
#else
	#define GETKEY(vkey) (GetKeyState(vkey) >> 15)
#endif

void generateGold(std::shared_ptr<DrawEngine::DrawEngine> drawEngine, int &totalGold)
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	int ammount = std::rand() % 50 + 1;
	for (totalGold = 0; totalGold != ammount; totalGold++)
	{
		int x = std::rand() % (drawEngine->GetColumns() - 1) + 1;
		int y = std::rand() % (drawEngine->GetRows() - 1) + 1;
		wchar_t currentChar = drawEngine->GetChar(x, y);
		if (currentChar != TEXT('+') && currentChar != TEXT('@') && currentChar != TEXT('&'))
			drawEngine->DrawPixel(TEXT('#'), x, y, 14);
		else totalGold--;
	}
}

int main()
{
	HWND consoleWindow = GetConsoleWindow();
	SetConsoleTitle(TEXT("DemoGame"));
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

	try
	{
		auto game = std::make_unique<DemoGame::Game>(TEXT('@'), 10, 10); //new game instance, spawn player (@) at x: 10 y: 10
		game->SetWallCharacter(TEXT('+')); //sets the character that will act as a wall
		auto drawEngine = game->GetDrawEngine(); //get DrawEngine instance
		drawEngine->FillScreen(TEXT(' ')); //create blank screen
		drawEngine->PutText(TEXT("+ = wall"), 20, 11);
		drawEngine->PutText(TEXT("@ = player"), 20, 12);
		drawEngine->PutText(TEXT("# = gold coin"), 20, 13);
		drawEngine->PutText(TEXT("W, A, S, D, Up Arrow, Down Arrow, Left Arrow, Right Arrow = movement"), 20, 14);
		drawEngine->PutText(TEXT("Press Enter to continue (or Esc to exit)"), 20, 15);
		drawEngine->Draw(); //write changes to console screen
		WAIT(0.1);
		while (true) {
			if (consoleWindow == GetForegroundWindow())
			{
				if (GETKEY(VK_RETURN))
					break;
				else if (GETKEY(VK_ESCAPE))
					goto end;
			}
		}
		drawEngine->FillScreen(TEXT(' '));
	
		drawEngine->DrawPixel(TEXT('@'), game->GetPlayerX(), game->GetPlayerY(), 10);
	
		drawEngine->DrawRectangle(TEXT('+'), 0, 1, 11, 1);
		drawEngine->DrawRectangle(TEXT('+'), 10, 0, 1, 1);

		int totalGold = 0;
		generateGold(drawEngine, totalGold);
		auto &score = game->GetScore();

		while (true) {
			if (consoleWindow == GetForegroundWindow())
			{
				if (GETKEY(VK_ESCAPE))
					break;
				else if (GETKEY(0x57/*W*/) || GETKEY(VK_UP))
					game->MovePlayerUp();
				else if (GETKEY(0x41/*A*/) || GETKEY(VK_LEFT))
					game->MovePlayerLeft();
				else if (GETKEY(0x53/*S*/) || GETKEY(VK_DOWN))
					game->MovePlayerDown();
				else if (GETKEY(0x44/*D*/) || GETKEY(VK_RIGHT))
					game->MovePlayerRight();
			}

			if (score > 9999) score = 9999;
			if (score == totalGold)
			{
				if (MessageBox(NULL, TEXT("You got all of the gold! Play again?"), TEXT("Congrats!"), MB_YESNO) != IDYES)
					break;
				score = 0;
				totalGold = 0;
				drawEngine->DrawRectangle(TEXT(' '), 0, 0, 10, 1);
				generateGold(drawEngine, totalGold);
			}
			auto scoreString = TEXT("Gold: ") + DrawEngine::to_gstring(score);
			drawEngine->PutText(scoreString.c_str(), 0, 0);
			drawEngine->Draw();
		}
	}
	catch (DrawEngine::gstring_t exceptionMessage)
	{
		MessageBox(consoleWindow, exceptionMessage.c_str(), TEXT("Error"), MB_OK | MB_ICONERROR);
	}

	end:
	return 0;
}
