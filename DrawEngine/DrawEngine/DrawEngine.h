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

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <conio.h>

#include <Windows.h>

#ifdef UNICODE
typedef wchar_t gchar_t;
typedef std::wstring gstring_t;
#define GCHARLEN wcslen
#define TOGSTRING std::to_wstring
#else
typedef char gchar_t;
typedef std::string gstring_t;
#define GCHARLEN strlen
#define TOGSTRING std::to_string
#endif

class DrawEngine
{
private:
	gchar_t Map[UCHAR_MAX][UCHAR_MAX]; //Map[x][y]
	WORD MapAttributes[UCHAR_MAX][UCHAR_MAX];

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE stdOutputHandle;
	int columns = 0; //x
	int rows = 0; //y
public:
	DrawEngine();

	void FillScreen(gchar_t letter, WORD attributes = 7);
	void DrawPixel(gchar_t letter, int x, int y, WORD attributes = 7);
	void DrawRectangle(gchar_t letter, int x, int y, int l, int thickness, WORD attributes = 7);
	void DrawEmptyRectangle(gchar_t letter, int x, int y, int l, int w, WORD attributes = 7);
	void PutText(gstring_t text, int x, int y, WORD attributes = 7);
	gchar_t GetChar(int x, int y);

	void Draw();
	int GetColumns() { return columns; }
	int GetRows() { return rows; }
};
