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
	wchar_t Map[UCHAR_MAX][UCHAR_MAX]; //Map[x][y]
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE stdOutputHandle;
	int columns = 0; //x
	int rows = 0; //y
public:
	DrawEngine();
	void FillScreen(wchar_t letter);
	void DrawSinglePixel(wchar_t letter, int x, int y);
	void DrawLine(wchar_t letter, int x, int y, int l, int thickness);
	void DrawBox(wchar_t letter, int x, int y, int l, int w);
	void PutText(std::wstring text, int x, int y);
	wchar_t GetChar(int x, int y);
	void Draw();
	int GetColumns() { return columns; }
	int GetRows() { return rows; }
};
