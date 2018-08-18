#include "Game.h"

#define wait(x) Sleep((DWORD)(x * 1000))
#define pause() fputs("Press any key to continue . . . ", stdout); _getch(); putc('\n', stdout);
#define GetKey(vkey) (GetKeyState(vkey) >> 15) //If vkey is down, the high bit is 1

Game *game;

int totalgold;

void generateGold()

{
	srand((unsigned int)time(nullptr));
	int ammount = rand() % 51;
	for (totalgold = 0; totalgold != ammount; totalgold++)
	{
		int x = rand() % (game->de->GetColumns() - 2);
		int y = rand() % (game->de->GetRows() - 2);
		x += 2; y += 2;
		wchar_t a = game->de->GetChar(x, y);
		if (a != TEXT('+') && a != TEXT('@') && a != TEXT('&'))
			game->de->DrawSinglePixel('#', x, y);
		else totalgold--;
	}
}

bool multiplayer = false;

int main()
{
	SetConsoleTitle(TEXT("APSubmission"));

	try
	{
		game = new Game(TEXT('@'), 10, 10); //new game instance, spawn player (@) at x: 10 y: 10
		game->SetWallCharacter(TEXT('+')); //sets the character that will act as a wall
	
		game->de->FillScreen(TEXT(' '));
		game->de->PutText(TEXT("+ = wall"), 20, 11);
		game->de->PutText(TEXT("@ = player"), 20, 12);
		game->de->PutText(TEXT("# = gold coin"), 20, 13);
		game->de->PutText(TEXT("W, A, S, D, Up Arrow, Down Arrow, Left Arrow, Right Arrow = movement"), 20, 14);
		game->de->PutText(TEXT("Press Enter to continue (or Esc to exit)"), 20, 15);
		game->de->Draw();
		wait(0.1);
		while (true) {
			if (GetConsoleWindow() == GetForegroundWindow())
			{
				if (GetKey(VK_RETURN))
					break;
				else if (GetKey(VK_ESCAPE))
					goto end;
			}
		}
		game->de->FillScreen(' ');
	
		game->de->DrawSinglePixel('@', game->GetPlayerX(), game->GetPlayerY());
	
		game->de->DrawLine('+', 0, 1, 11, 1);
		game->de->DrawLine('+', 10, 0, 1, 1);
	
		generateGold();
	
		while (true) {
			if (GetConsoleWindow() == GetForegroundWindow())
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
			if (game->score == totalgold)
			{
				if (MessageBox(NULL, TEXT("You got all of the gold! Play again?"), TEXT("Congrats!"), MB_YESNO) == IDYES)
				{
					game->score = 0;
					totalgold = 0;
					game->de->DrawLine(' ', 0, 0, 10, 1);
					generateGold();
				}
				else break;
			}
			std::wstring scstr = TEXT("Gold: ") + std::to_wstring(game->score);
			game->de->PutText(scstr.c_str(), 0, 0);
			game->de->Draw();
		}
		end:
		delete game;
	}
	catch (std::exception e)
	{
		std::cerr << e.what() << std::endl;
		pause();
	}
	return 0;
}