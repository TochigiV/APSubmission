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
	printf("\nPress enter to continue . . .\n");
	getchar();
}

de DrawEngine;

int main()
{
	SetConsoleTitle(L"APSubmission");
	//pause();
	DrawEngine.Init();
	while (true) {
		DrawEngine.FillScreen('@');
		pause();
		wait(1 / 60);
	}
	//pause();
	return 0;
}