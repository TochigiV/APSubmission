#include "DrawEngine.h"

void DrawEngine::FillScreen(char letter)
{
	for (int y = 0; y < rows; y++)
		for (int x = 0; x < columns; x++)
			Map[y][x] = letter;
}

void DrawEngine::DrawSinglePixel(char letter, int x, int y)
{
	Map[y][x] = letter;
}

void DrawEngine::DrawRect(char letter, int x, int y, int l, int w)
{
	for (int a = x; a < (l + x); a++)
		Map[y][a] = letter;
	for (int b = y; b < (w + y); b++)
		Map[b][x] = letter;
}

void DrawEngine::DrawBox(char letter, int x, int y, int w, int l, int thickness)
{
	DrawRect(letter, x, y, w, thickness);
	DrawRect(letter, x, y, thickness, l);
	DrawRect(letter, (x + w) - 1, y, thickness, w);
	DrawRect(letter, x, (y + l) - 1, l, thickness);
}

void DrawEngine::DrawTextA(const char* text, int x, int y)
{
	std::string t(text);
	std::vector<char> chars(t.begin(), t.end());
	for (int i = 0; i < chars.size(); i++)
	{
		Map[y][x + i] = chars[i];
	}
}

char DrawEngine::GetChar(int x, int y)
{
	return Map[y][x];
}

void DrawEngine::Draw()
{
	for (int y = 0; y < rows; y++)
		for (int x = 0; x < columns; x++)
			putchar(Map[y][x]);
}

DrawEngine::DrawEngine()
{
	FillScreen(' ');
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

DrawEngine::~DrawEngine()
{
	//nothing
}