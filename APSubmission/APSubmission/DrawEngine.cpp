#include "DrawEngine.h"
#include <Windows.h>

void FillScreen(char letter)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	int columns = csbi.srWindow.Right - (csbi.srWindow.Left + 1);
	int rows = csbi.srWindow.Bottom - (csbi.srWindow.Top + 1);

	for (int a = 0; a <= (rows + 1); a++)
		for (int i = 0; i <= (columns + 1); i++)
			putchar(letter);
}