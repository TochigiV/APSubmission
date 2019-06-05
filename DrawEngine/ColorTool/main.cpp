#include <Windows.h>
#include <iostream>
#include <string>
#include <conio.h>

#define PAUSE() fputs("Press any key to continue . . . ", stdout); _getch(); fputc('\n', stdout);

int main()
{
	HANDLE stdOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i != 255; i++)
	{
		SetConsoleTextAttribute(stdOutputHandle, i);
		std::cout << "Text attribute #" << i << std::endl;
	}
	SetConsoleTextAttribute(stdOutputHandle, 7);
	PAUSE();
	return 0;
}