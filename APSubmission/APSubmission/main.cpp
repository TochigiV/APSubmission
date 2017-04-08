#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <Windows.h>
#include <algorithm>
#include <time.h>

#include "DrawEngine.h"

#define wait(x) Sleep(x * 1000)

void pause()
{
	getchar();
}

DrawEngine *de;

void LogicThread()
{
	while (true)
	{
		de->Draw();
		Sleep(0.2 * 1000);
	}
}

int main()
{
	SetConsoleTitle(L"APSubmission");
	de = new DrawEngine();
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)LogicThread, NULL, NULL, NULL);
	de->FillScreen('@');
	de->DrawBox('+', 0, 0, 20, 20, 1);
	pause();
	return 0;
}