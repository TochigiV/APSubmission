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

DrawEngine *de;

int main()
{
	SetConsoleTitle(L"APSubmission");
	de = new DrawEngine();
	de->FillScreen('@');
	pause();
	delete de;
	return 0;
}