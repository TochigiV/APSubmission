#pragma once

#include "stdafx.h"

class DrawEngine
{
private:
	char Map[UCHAR_MAX][UCHAR_MAX]; //Map[y][x]
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE stdHandle;
	void cls();
public:
	int columns = 0; //x
	int rows = 0; //y
	DrawEngine();
	void FillScreen(char letter);
	void DrawSinglePixel(char letter, int x, int y);
	void DrawRect(char letter, int x, int y, int l, int thickness);
	void DrawBox(char letter, int x, int y, int l, int w);
	void PutText(std::string text, int x, int y);
	char GetChar(int x, int y);
	void Draw();
	int GetColumns() { return columns; }
	int GetRows() { return rows; }
};