#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <Windows.h>

class DrawEngine
{
private:
	int columns = 0; //x
	int rows = 0; //y
	char Map[UCHAR_MAX][UCHAR_MAX]; //Map[y][x]
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	void cls();
public:
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