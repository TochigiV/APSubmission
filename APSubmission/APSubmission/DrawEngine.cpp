#include "DrawEngine.h"

void dEngine::FillScreen(char letter)
{
	for (int a = 0; a <= (rows + 1); a++)
		for (int i = 0; i <= (columns + 1); i++)
			putchar(letter);
}

void dEngine::DrawLine(char letter, int x, int y, int w, int h)
{

}

void dEngine::Init()
{
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - (csbi.srWindow.Left + 1);
	rows = csbi.srWindow.Bottom - (csbi.srWindow.Top + 1);
}