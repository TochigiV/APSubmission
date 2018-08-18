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
	wchar_t Map[UCHAR_MAX][UCHAR_MAX]; //Map[y][x]
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE stdOutputHandle;
public:
	int columns = 0; //x
	int rows = 0; //y
	DrawEngine();
	void FillScreen(wchar_t letter);
	void DrawSinglePixel(wchar_t letter, int x, int y);
	void DrawRect(wchar_t letter, int x, int y, int l, int thickness);
	void DrawBox(wchar_t letter, int x, int y, int l, int w);
	void PutText(std::wstring text, int x, int y);
	wchar_t GetChar(int x, int y);
	void Draw();
	int GetColumns() { return columns; }
	int GetRows() { return rows; }
};