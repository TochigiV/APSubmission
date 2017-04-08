#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <Windows.h>

class dEngine
{
private:
	int columns;
	int rows;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
public:
	void Init();
	void FillScreen(char letter);
	void DrawLine(char letter, int x, int y, int w, int h);
};


extern dEngine DrawLine;