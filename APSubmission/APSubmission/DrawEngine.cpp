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

#define ThrowException(errstr) throw std::wstring(TEXT(errstr) TEXT("\n Error code: ") + std::to_wstring(GetLastError()));

void DrawEngine::FillScreen(wchar_t letter)
{
	for (int y = 0; y != rows; y++)
		for (int x = 0; x != columns; x++)
			Map[x][y] = letter;
}

void DrawEngine::DrawSinglePixel(wchar_t letter, int x, int y)
{
	Map[x][y] = letter;
}

void DrawEngine::DrawLine(wchar_t letter, int x, int y, int l, int thickness)
{
	for (int a = x; a != (l + x); a++)
		Map[a][y] = letter;
	for (int b = y; b != (thickness + y); b++)
		Map[x][b] = letter;
}

void DrawEngine::DrawBox(wchar_t letter, int x, int y, int l, int w)
{
	DrawLine(letter, x, y, l, 1);
	DrawLine(letter, x, y, 1, l);
	DrawLine(letter, (x + w) - 1, y, 1, l);
	DrawLine(letter, x, (y + l) - 1, l, 1);
}

void DrawEngine::PutText(std::wstring text, int x, int y)
{
	std::vector<wchar_t> chars(text.begin(), text.end());
	for (unsigned int i = 0; i != chars.size(); i++)
		Map[x + i][y] = chars[i];
}

wchar_t DrawEngine::GetChar(int x, int y)
{
	return Map[x][y];
}

void DrawEngine::Draw()
{
	for (int y = 0; y != rows; y++)
	{
		for (int x = 0; x != columns; x++)
		{
			wchar_t charFromBuffer;
			COORD location = { (SHORT)x, (SHORT)y };
			DWORD numberOfCharsRead;
			if (ReadConsoleOutputCharacter(stdOutputHandle, &charFromBuffer, 1, location, &numberOfCharsRead))
			{
				if (Map[x][y] != charFromBuffer)
				{
					DWORD numberOfCharsWritten;
					if (!WriteConsoleOutputCharacter(stdOutputHandle, &Map[x][y], (wcslen(&Map[x][y]) * sizeof(WCHAR)), location, &numberOfCharsWritten))
					{
						ThrowException("Failed to write to the console output at a given location!");
					}
				}
			}
			else
			{
				ThrowException("Failed to read from the console output at a given location!");
			}
		}
	}
}

DrawEngine::DrawEngine()
{
	stdOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (stdOutputHandle != INVALID_HANDLE_VALUE)
	{
		if (GetConsoleScreenBufferInfo(stdOutputHandle, &csbi))
		{
			columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
			rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

			COORD NewSBSize = { (SHORT)columns, (SHORT)rows };
			if (SetConsoleScreenBufferSize(stdOutputHandle, NewSBSize))
			{
				FillScreen(TEXT(' '));

				CONSOLE_CURSOR_INFO cursorInfo = { 1, FALSE };
				if (!SetConsoleCursorInfo(stdOutputHandle, &cursorInfo))
				{
					ThrowException("Failed to set the console cursor info!");
				}
			}
			else
			{
				ThrowException("Failed to set the console buffer size!");
			}
		}
		else
		{
			ThrowException("Failed to get the console buffer info!");
		}
	}
	else
	{
		ThrowException("Failed to get the console output handle!");
	}
}