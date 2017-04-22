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

void DrawEngine::DrawBox(char letter, int x, int y, int l, int w)
{
	DrawRect(letter, x, y, l, 1);
	DrawRect(letter, x, y, 1, l);
	DrawRect(letter, (x + w) - 1, y, 1, l);
	DrawRect(letter, x, (y + l) - 1, l, 1);
}

void DrawEngine::PutText(std::string text, int x, int y)
{
	std::vector<char> chars(text.begin(), text.end());
	for (int i = 0; i < chars.size(); i++)
	{
		Map[y][x + i] = chars[i];
	}
}

char DrawEngine::GetChar(int x, int y)
{
	return Map[y][x];
}

void DrawEngine::cls()
{
	COORD topLeft = { 0, 0 };
	DWORD length = csbi.dwSize.X * csbi.dwSize.Y;
	DWORD written;
	std::cout.flush();
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), L' ', length, topLeft, &written);
	FillConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE), csbi.wAttributes, length, topLeft, &written);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), topLeft);
}

void DrawEngine::Draw()
{
	cls();
	for (int y = 0; y < rows; y++)
		for (int x = 0; x < columns; x++)
			std::cout << Map[y][x];
}

DrawEngine::DrawEngine()
{
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	COORD NewSBSize = { columns, rows };
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), NewSBSize);
	FillScreen(' ');
}

DrawEngine::~DrawEngine()
{
	//nothing
}