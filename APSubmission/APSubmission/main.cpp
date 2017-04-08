#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <Windows.h>
#include <algorithm>
#include <time.h>

#include "DrawEngine.h"

#define wait(x) Sleep(x * 1000)

DrawEngine *de;

void LogicThread()
{
	while (true)
	{
		de->Draw();
		wait(0.2);
	}
}

int main()
{
	SetConsoleTitle(L"APSubmission");
	de = new DrawEngine();
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)LogicThread, NULL, NULL, NULL);
	de->DrawBox('+', 0, 0, 20, 20, 1);
	while (true) {
		if (GetAsyncKeyState(VK_ESCAPE))
			break;
	}
	return 0;
}