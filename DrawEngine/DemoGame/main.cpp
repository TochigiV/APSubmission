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

#define WAIT(x) Sleep((DWORD)(x * 1000))
#define PAUSE() fputs("Press any key to continue . . . ", stdout); _getch(); fputc('\n', stdout);

#define USE_ASYNC 1 //set to 0 if you want to use GetKeyState instead of GetAsyncKeyState
#if USE_ASYNC
	#define GETKEY(vkey) (GetAsyncKeyState(vkey) >> 15) //If vkey is down, the high bit is 1
#else
	#define GETKEY(vkey) (GetKeyState(vkey) >> 15) //If vkey is down, the high bit is 1
#endif

std::shared_ptr<Game> game;
std::shared_ptr<DrawEngine> drawEngine;

int totalGold;

void generateGold()
{
	srand((unsigned int)time(nullptr));
	int ammount = rand() % 51;
	for (totalGold = 0; totalGold != ammount; totalGold++)
	{
		int x = (rand() % (drawEngine->GetColumns() - 1)) + 1;
		int y = rand() % drawEngine->GetRows();
		wchar_t currentChar = drawEngine->GetChar(x, y);
		if (currentChar != TEXT('+') && currentChar != TEXT('@') && currentChar != TEXT('&'))
			drawEngine->DrawPixel(TEXT('#'), x, y);
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
		game = std::make_shared<Game>(TEXT('@'), 10, 10); //new game instance, spawn player (@) at x: 10 y: 10
		game->SetWallCharacter(TEXT('+')); //sets the character that will act as a wall
		drawEngine = std::dynamic_pointer_cast<DrawEngine>(game->drawEngine);

		drawEngine->FillScreen(TEXT(' '));
		drawEngine->PutText(TEXT("+ = wall"), 20, 11);
		drawEngine->PutText(TEXT("@ = player"), 20, 12);
		drawEngine->PutText(TEXT("# = gold coin"), 20, 13);
		drawEngine->PutText(TEXT("W, A, S, D, Up Arrow, Down Arrow, Left Arrow, Right Arrow = movement"), 20, 14);
		drawEngine->PutText(TEXT("Press Enter to continue (or Esc to exit)"), 20, 15);
		drawEngine->Draw();
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
	
		drawEngine->DrawPixel(TEXT('@'), game->GetPlayerX(), game->GetPlayerY());
	
		drawEngine->DrawRectangle(TEXT('+'), 0, 1, 11, 1);
		drawEngine->DrawRectangle(TEXT('+'), 10, 0, 1, 1);

		generateGold();
	
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
	
			if (game->score > 9999) game->score = 9999;
			if (game->score == totalGold)
			{
				if (MessageBox(NULL, TEXT("You got all of the gold! Play again?"), TEXT("Congrats!"), MB_YESNO) != IDYES)
					break;
				game->score = 0;
				totalGold = 0;
				drawEngine->DrawRectangle(TEXT(' '), 0, 0, 10, 1);
				generateGold();
			}
#ifdef UNICODE
			std::wstring scoreString = TEXT("Gold: ") + std::to_wstring(game->score);
#else
			std::string scoreString = TEXT("Gold: ") + std::to_string(game->score);
#endif
			drawEngine->PutText(scoreString.c_str(), 0, 0);
			drawEngine->Draw();
		}
	}

#ifdef UNICODE
	catch (std::wstring exceptionMessage)
#else 
	catch (std::string exceptionMessage)
#endif

	{
		MessageBox(consoleWindow, exceptionMessage.c_str(), TEXT("Error"), MB_OK | MB_ICONERROR);
	}
	end:
	return 0;
}
