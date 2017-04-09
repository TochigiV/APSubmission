#include "DrawEngine.h"

/*
0= 
1=@
2=+
3=#
*/

int letterToInt(char letter)
{
	if (letter == '@')
		return 1;
	else if (letter == '+')
		return 2;
	else if (letter == '#')
		return 3;
	else
		return 0;
}

char intToLetter(int val)
{
	if (val == 0)
		return ' ';
	else if (val == 1)
		return '@';
	else if (val == 2)
		return '+';
	else if (val == 3)
		return '#';
	else return ' ';
}

void DrawEngine::FillScreen(char letter)
{
	for (int y = 0; y < rows; y++)
		for (int x = 0; x < columns; x++)
			Map[y][x] = letterToInt(letter);
}

void DrawEngine::DrawSinglePixel(char letter, int x, int y)
{
	Map[y][x] = letterToInt(letter);
}

void DrawEngine::DrawRect(char letter, int x, int y, int l, int w)
{
	int la = l;
	int wa = w;
	for (int a = x; a < (la + x); a++)
		Map[y][a] = letterToInt(letter);
	for (int b = y; b < (wa + y); b++)
		Map[b][x] = letterToInt(letter);
}

void DrawEngine::DrawBox(char letter, int x, int y, int w, int l, int thickness)
{
	DrawRect(letter, x, y, w, thickness);
	DrawRect(letter, x, y, thickness, l);
	DrawRect(letter, (x + w)-1, y, thickness, w);
	DrawRect(letter, x, (y + l)-1, l, thickness);
}

char DrawEngine::GetLetter(int x, int y)
{
	return intToLetter(Map[y][x]);
}

void DrawEngine::Draw()
{
	for (int y = 0; y < rows; y++)
		for (int x = 0; x < columns; x++)
			putchar(intToLetter(Map[y][x]));
}

DrawEngine::DrawEngine()
{
	FillScreen(' ');
}