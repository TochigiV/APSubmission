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
	int la = l;
	int wa = w;
	for (int a = x; a < (la + x); a++)
		Map[y][a] = letter;
	for (int b = y; b < (wa + y); b++)
		Map[b][x] = letter;
}

void DrawEngine::DrawBox(char letter, int x, int y, int w, int l, int thickness)
{
	DrawRect(letter, x, y, w, thickness);
	DrawRect(letter, x, y, thickness, l);
	DrawRect(letter, (x + w) - 1, y, thickness, w);
	DrawRect(letter, x, (y + l) - 1, l, thickness);
}

char DrawEngine::GetLetter(int x, int y)
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
}