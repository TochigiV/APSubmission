#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <Windows.h>

class DrawEngine
{
private:
	int columns = 120;
	int rows = 30;
	char Map[255][255]; //Map[y][x]
	CONSOLE_SCREEN_BUFFER_INFO csbi;
public:
	DrawEngine();
	~DrawEngine();
	void FillScreen(char letter);
	void DrawSinglePixel(char letter, int x, int y);
	void DrawRect(char letter, int x, int y, int l, int thickness);
	void DrawBox(char letter, int x, int y, int l, int w, int thickness);
	void DrawTextA(const char* text, int x, int y);
	char GetLetter(int x, int y);
	void Draw();
	int GetColumns() { return columns; }
	int GetRows() { return rows; }
};