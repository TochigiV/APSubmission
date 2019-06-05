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

#include "DrawEngine.h"

#ifdef UNICODE
#define THROWEXCEPTION(errstr) throw std::wstring(TEXT(errstr) TEXT("\n Error code: ") + std::to_wstring(GetLastError()));
#else
#define THROWEXCEPTION(errstr) throw std::string(TEXT(errstr) TEXT("\n Error code:") + std::to_string(GetLastError()));
#endif

#ifdef UNICODE
void DrawEngine::FillScreen(wchar_t letter, WORD attributes)
#else
void DrawEngine::FillScreen(char letter, WORD attributes)
#endif
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

#ifdef UNICODE
void DrawEngine::DrawPixel(wchar_t letter, int x, int y, WORD attributes)
#else
void DrawEngine::DrawPixel(char letter, int x, int y, WORD attributes)
#endif
{
	Map[x][y] = letter;
	MapAttributes[x][y] = attributes;
}

#ifdef UNICODE
void DrawEngine::DrawRectangle(wchar_t letter, int x, int y, int l, int w, WORD attributes)
#else
void DrawEngine::DrawRectangle(char letter, int x, int y, int l, int w, WORD attributes)
#endif
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

#ifdef UNICODE
void DrawEngine::DrawEmptyRectangle(wchar_t letter, int x, int y, int l, int w, WORD attributes)
#else
void DrawEngine::DrawEmptyRectangle(char letter, int x, int y, int l, int w, WORD attributes)
#endif
{
	DrawRectangle(letter, x, y, l, 1, attributes);
	DrawRectangle(letter, x, y, 1, l, attributes);
	DrawRectangle(letter, (x + w) - 1, y, 1, l, attributes);
	DrawRectangle(letter, x, (y + l) - 1, l, 1, attributes);
}

#ifdef UNICODE
void DrawEngine::PutText(std::wstring text, int x, int y, WORD attributes)
#else
void DrawEngine::PutText(std::string text, int x, int y, WORD attributes)
#endif
{
	for (unsigned int i = 0; i != text.length(); i++)
	{
		Map[x + i][y] = text[i];
		MapAttributes[x + i][y] = attributes;
	}
}

#ifdef UNICODE
wchar_t DrawEngine::GetChar(int x, int y)
#else
char DrawEngine::GetChar(int x, int y)
#endif
{
	return Map[x][y];
}

void DrawEngine::Draw()
{
	for (int y = 0; y != rows; y++)
	{
		for (int x = 0; x != columns; x++)
		{

#ifdef UNICODE
			wchar_t charFromBuffer;
#else
			char charFromBuffer;
#endif

			COORD location = { (SHORT)x, (SHORT)y };

			DWORD numberOfCharsRead;

			if (!ReadConsoleOutputCharacter(stdOutputHandle, &charFromBuffer, 1, location, &numberOfCharsRead))
				THROWEXCEPTION("Failed to read from the console output at a given location!");

			if (Map[x][y] != charFromBuffer)
			{

				DWORD numberOfCharsWritten;
#ifdef UNICODE
				if (!WriteConsoleOutputCharacter(stdOutputHandle, &Map[x][y], (wcslen(&Map[x][y]) * sizeof(WCHAR)), location, &numberOfCharsWritten))
#else
				if (!WriteConsoleOutputCharacter(stdOutputHandle, &Map[x][y], (strlen(&Map[x][y]) * sizeof(WCHAR)), location, &numberOfCharsWritten))
#endif
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

	if (!SetConsoleTextAttribute(stdOutputHandle, 255))
		THROWEXCEPTION("Failed to set console text attributes!");
}