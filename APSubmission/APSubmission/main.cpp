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

DrawEngine de;

int main()
{
	SetConsoleTitle(L"APSubmission");
	//pause();
	de.Init();
	while (true) {
		de.FillScreen('@');
		pause();
		wait(1 / 60);
	}
	//pause();
	return 0;
}