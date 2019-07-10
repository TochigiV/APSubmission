/*
MIT License

Copyright (c) 2019 Tochigi

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

#include "DrawEngine.h"

#define THROWEXCEPTION(errstr) throw gstring_t(TEXT(errstr) TEXT("\n Error code: ") + TOGSTRING(GetLastError()));

void DrawEngine::FillScreen(gchar_t letter, WORD attributes)
{
	for (int y = 0; y != rows; y++)
	{
		for (int x = 0; x != columns; x++)
		{
			Map[x][y] = letter;
			MapAttributes[x][y] = attributes;
		}
	}
			
}

void DrawEngine::DrawPixel(gchar_t letter, int x, int y, WORD attributes)
{
	Map[x][y] = letter;
	MapAttributes[x][y] = attributes;
}

void DrawEngine::DrawRectangle(gchar_t letter, int x, int y, int l, int w, WORD attributes)
{
	for (int a = x; a != (l + x); a++)
	{
		Map[a][y] = letter;
		MapAttributes[x][y] = attributes;
	}
	for (int b = y; b != (w + y); b++)
	{
		Map[x][b] = letter;
		MapAttributes[x][y] = attributes;
	}
}

void DrawEngine::DrawEmptyRectangle(gchar_t letter, int x, int y, int l, int w, WORD attributes)
{
	DrawRectangle(letter, x, y, l, 1, attributes);
	DrawRectangle(letter, x, y, 1, l, attributes);
	DrawRectangle(letter, (x + w) - 1, y, 1, l, attributes);
	DrawRectangle(letter, x, (y + l) - 1, l, 1, attributes);
}

void DrawEngine::PutText(gstring_t text, int x, int y, WORD attributes)
{
	for (unsigned int i = 0; i != text.length(); i++)
	{
		Map[x + i][y] = text[i];
		MapAttributes[x + i][y] = attributes;
	}
}

gchar_t DrawEngine::GetChar(int x, int y)
{
	return Map[x][y];
}

void DrawEngine::Draw()
{
	for (int y = 0; y != rows; y++)
	{
		for (int x = 0; x != columns; x++)
		{
			gchar_t charFromBuffer;

			COORD location = { (SHORT)x, (SHORT)y };

			DWORD numberOfCharsRead;

			if (!ReadConsoleOutputCharacter(stdOutputHandle, &charFromBuffer, 1, location, &numberOfCharsRead))
				THROWEXCEPTION("Failed to read from the console output at a given location!");

			if (Map[x][y] != charFromBuffer)
			{

				DWORD numberOfCharsWritten;
				if (!WriteConsoleOutputCharacter(stdOutputHandle, &Map[x][y], (GCHARLEN(&Map[x][y]) * sizeof(gchar_t)), location, &numberOfCharsWritten))
					THROWEXCEPTION("Failed to write to the console output at a given location!");

				DWORD numberOfAttributesWritten;

				if (!WriteConsoleOutputAttribute(stdOutputHandle, &MapAttributes[x][y], 1, location, &numberOfAttributesWritten))
					THROWEXCEPTION("Failed to set console text attributes at a given location!");

			}
		}
	}
}

DrawEngine::DrawEngine()
{
	stdOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (stdOutputHandle == INVALID_HANDLE_VALUE)
		THROWEXCEPTION("Failed to get the console output handle!");

	if (!GetConsoleScreenBufferInfo(stdOutputHandle, &csbi))
		THROWEXCEPTION("Failed to get the console buffer info!");

	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	COORD newScreenBufferSize = { (SHORT)columns, (SHORT)rows };
	if (!SetConsoleScreenBufferSize(stdOutputHandle, newScreenBufferSize))
		THROWEXCEPTION("Failed to set the console buffer size!");

	FillScreen(TEXT(' '));

	CONSOLE_CURSOR_INFO cursorInfo = { 1, FALSE };
	if (!SetConsoleCursorInfo(stdOutputHandle, &cursorInfo))
		THROWEXCEPTION("Failed to set the console cursor info!");
}