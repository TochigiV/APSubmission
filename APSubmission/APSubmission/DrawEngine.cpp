#include "DrawEngine.h"

#define ThrowException(errstr) throw std::exception(std::string(errstr "\nError code: " + std::to_string(GetLastError())).c_str());

void DrawEngine::FillScreen(wchar_t letter)
{
	for (int y = 0; y < rows; y++)
		for (int x = 0; x < columns; x++)
			Map[x][y] = letter;
}

void DrawEngine::DrawSinglePixel(wchar_t letter, int x, int y)
{
	Map[x][y] = letter;
}

void DrawEngine::DrawLine(wchar_t letter, int x, int y, int l, int thickness)
{
	for (int a = x; a < (l + x); a++)
		Map[a][y] = letter;
	for (int b = y; b < (thickness + y); b++)
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
	for (unsigned int i = 0; i < chars.size(); i++)
		Map[x + i][y] = chars[i];
}

wchar_t DrawEngine::GetChar(int x, int y)
{
	return Map[x][y];
}

void DrawEngine::Draw()
{
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < columns; x++)
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
				ThrowException("Failed to read the console output character at a given location!");
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
					ThrowException("Failed to set console cursor info!");
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