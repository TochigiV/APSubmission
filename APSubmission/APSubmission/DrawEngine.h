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
	int Map[30][120];
public:
	DrawEngine();
	void FillScreen(char letter);
	void DrawLine(char letter, int x, int y, int l, int thickness);
	void DrawBox(char letter, int x, int y, int l, int w, int thickness);
	void Draw();
};