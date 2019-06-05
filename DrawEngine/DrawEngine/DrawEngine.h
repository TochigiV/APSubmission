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

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <conio.h>

#include <Windows.h>

class DrawEngine
{
private:

#ifdef UNICODE
	wchar_t Map[UCHAR_MAX][UCHAR_MAX]; //Map[x][y]
#else
	char Map[UCHAR_MAX][UCHAR_MAX];
#endif
	WORD MapAttributes[UCHAR_MAX][UCHAR_MAX];

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE stdOutputHandle;
	int columns = 0; //x
	int rows = 0; //y
public:
	DrawEngine();

#ifdef UNICODE
	void FillScreen(wchar_t letter, WORD attributes = 7);
	void DrawPixel(wchar_t letter, int x, int y, WORD attributes = 7);
	void DrawRectangle(wchar_t letter, int x, int y, int l, int thickness, WORD attributes = 7);
	void DrawEmptyRectangle(wchar_t letter, int x, int y, int l, int w, WORD attributes = 7);
	void PutText(std::wstring text, int x, int y, WORD attributes = 7);
	wchar_t GetChar(int x, int y);
#else
	void FillScreen(char letter, WORD attributes = 7);
	void DrawPixel(char letter, int x, int y, WORD attributes = 7);
	void DrawEmptyRectangle(char letter, int x, int y, int l, int thickness, WORD attributes = 7);
	void DrawRectangle(char letter, int x, int y, int l, int w, WORD attributes = 7);
	void PutText(std::string text, int x, int y, WORD attributes = 7);
	char GetChar(int x, int y);
#endif

	void Draw();
	int GetColumns() { return columns; }
	int GetRows() { return rows; }
};
