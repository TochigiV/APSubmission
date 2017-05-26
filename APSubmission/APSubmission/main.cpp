#include "stdafx.h"

#include <stdlib.h>
#include <time.h>

#include "Game.h"

#include "json.hpp"

#define wait(x) Sleep((DWORD)(x * 1000))
#define BUFF_SIZE 512

Game *game;

int totalgold;

void generateGold()
{
	srand((unsigned int)time(nullptr));
	int ammount = rand() % 51;
	for (totalgold = 0; totalgold < ammount; totalgold++)
	{
		int x = rand() % (game->de->GetColumns() - 2);
		int y = rand() % (game->de->GetRows() - 2);
		x += 2; y += 2;
		char a = game->de->GetChar(x, y);
		if (a != '+' && a != '@' && a != '&')
			game->de->DrawSinglePixel('#', x, y);
		else totalgold--;
	}
}

bool multiplayer = false;

DWORD GetRegKey(HKEY hKey, std::string strValueName)
{
	DWORD dwBufferSize = sizeof(DWORD);
	DWORD nResult;
	DWORD nError = RegQueryValueExA(hKey, strValueName.c_str(), NULL, NULL, reinterpret_cast<LPBYTE>(&nResult), &dwBufferSize);
	if (!nError) return nResult;
	return nError;
}

int main()
{
	SetConsoleTitle(L"APSubmission");
	setvbuf(stdout, NULL, _IOFBF, 514);

	HKEY hKey;
	DWORD key = RegOpenKeyExA(HKEY_CURRENT_USER, "Console", NULL, KEY_READ, &hKey);
	if (key == 0 && key != 2)
	{
		if (GetRegKey(hKey, "ForceV2") != 0)
		{
			std::cout << "Legacy console is not enabled! Please enable the legacy console to play this game." << std::endl;
			system("pause");
			return 0;
		}
	}

	game = new Game('@', 10, 10); //new game instance, spawn player (@) at x: 10 y: 10
	game->SetWallCharacter('+'); //sets the character that will act as a wall

	game->de->FillScreen(' ');
	game->de->PutText("+ = wall", 20, 11);
	game->de->PutText("@ = player", 20, 12);
	game->de->PutText("# = gold coin", 20, 13);
	game->de->PutText("W, A, S, D, Up Arrow, Down Arrow, Left Arrow, Right Arrow = movement", 20, 14);
	game->de->PutText("Press Enter to continue (or Esc to exit)", 20, 15);
	game->de->PutText("Press M to connect to a server", 20, 16);
	game->de->Draw();
	wait(0.1);
	while (true) {
		if (GetConsoleWindow() == GetForegroundWindow())
		{
			if (GetAsyncKeyState(VK_RETURN))
				break;
			else if (GetAsyncKeyState(VK_ESCAPE))
				exit(0);
			else if (GetAsyncKeyState(0x4D))
			{
				multiplayer = true;
				break;
			}
		}
	}
	if (!multiplayer)
	{
		game->de->FillScreen(' ');

		game->de->DrawSinglePixel('@', game->GetPlayerX(), game->GetPlayerY());

		game->de->DrawRect('+', 0, 1, 11, 1);
		game->de->DrawRect('+', 10, 0, 1, 1);

		generateGold();

		while (true) {
			if (GetConsoleWindow() == GetForegroundWindow())
			{
				if (GetAsyncKeyState(VK_ESCAPE))
					break;
				else if (GetAsyncKeyState(0x57/*W*/) || GetAsyncKeyState(VK_UP))
					game->MovePlayerUp();
				else if (GetAsyncKeyState(0x41/*A*/) || GetAsyncKeyState(VK_LEFT))
					game->MovePlayerLeft();
				else if (GetAsyncKeyState(0x53/*S*/) || GetAsyncKeyState(VK_DOWN))
					game->MovePlayerDown();
				else if (GetAsyncKeyState(0x44/*D*/) || GetAsyncKeyState(VK_RIGHT))
					game->MovePlayerRight();
			}

			if (game->score > 9999) game->score = 9999;
			if (game->score == totalgold)
			{
				if (MessageBox(NULL, L"You got all of the gold! Play again?", L"Congrats!", MB_YESNO) == IDYES)
				{
					game->score = 0;
					totalgold = 0;
					game->de->DrawRect(' ', 0, 0, 10, 1);
					generateGold();
				}
				else break;
			}
			std::string scstr = "Gold: " + std::to_string(game->score);
			game->de->PutText(scstr.c_str(), 0, 0);
			game->de->Draw(); //re-draw the scene
			wait(0.1); //10 fps
		}
	}
	else
	{
		game->de->FillScreen(' ');

		std::cout << "Server IP: ";
		std::string input;
		std::cin >> input;

		std::cout << "Server Port: ";
		unsigned short pinput;
		std::cin >> pinput;

	select_char:
		std::cout << "Server Character: ";
		std::string cha;
		std::cin >> cha;
		if (cha.size() > 1)
		{
			std::cout << "Please choose a single character!" << std::endl;
			goto select_char;
		}

		game->SetPCharacter(cha[0]);

		RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance();
		RakNet::Packet *packet;

		peer->Startup(1, &RakNet::SocketDescriptor(), 1);
		peer->Connect(input.c_str(), pinput, 0, 0);

		bool breaker = false;
		while (true)
		{
			for (packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive())
			{
				if(packet->data[2] == '1')
				{
					std::string chunk1_json;
					for (unsigned int i = 3; i < packet->length; i++)
						chunk1_json += packet->data[i];
					json::JSON chunk1 = json::JSON::Load(chunk1_json);
					for (int y = 0; y < 5; y++)
					{
						for (int x = 0; x < 120; x++)
						{
							game->de->DrawSinglePixel(static_cast<char>(chunk1[y][x].ToInt()), x, y);
						}
					}
				}
				else if (packet->data[2] == '2')
				{
					std::string chunk2_json;
					for (unsigned int i = 3; i < packet->length; i++)
						chunk2_json += packet->data[i];
					json::JSON chunk2 = json::JSON::Load(chunk2_json);
					for (int y = 5; y < 10; y++)
					{
						for (int x = 0; x < 120; x++)
						{
							game->de->DrawSinglePixel(static_cast<char>(chunk2[y][x].ToInt()), x, y);
						}
					}
				}
				else if (packet->data[2] == '3')
				{
					std::string chunk3_json;
					for (unsigned int i = 3; i < packet->length; i++)
						chunk3_json += packet->data[i];
					json::JSON chunk3 = json::JSON::Load(chunk3_json);
					for (int y = 10; y < 15; y++)
					{
						for (int x = 0; x < 120; x++)
						{
							game->de->DrawSinglePixel(static_cast<char>(chunk3[y][x].ToInt()), x, y);
						}
					}
				}
				else if (packet->data[2] == '4')
				{
					std::string chunk4_json;
					for (unsigned int i = 3; i < packet->length; i++)
						chunk4_json += packet->data[i];
					json::JSON chunk4 = json::JSON::Load(chunk4_json);
					for (int y = 15; y < 20; y++)
					{
						for (int x = 0; x < 120; x++)
						{
							game->de->DrawSinglePixel(static_cast<char>(chunk4[y][x].ToInt()), x, y);
						}
					}
				}
				else if (packet->data[2] == '5')
				{
					std::string chunk5_json;
					for (unsigned int i = 3; i < packet->length; i++)
						chunk5_json += packet->data[i];
					json::JSON chunk5 = json::JSON::Load(chunk5_json);
					for (int y = 20; y < 25; y++)
					{
						for (int x = 0; x < 120; x++)
						{
							game->de->DrawSinglePixel(static_cast<char>(chunk5[y][x].ToInt()), x, y);
						}
					}
				}
				else if (packet->data[2] == '6')
				{
					std::string chunk6_json;
					for (unsigned int i = 3; i < packet->length; i++)
						chunk6_json += packet->data[i];
					json::JSON chunk6 = json::JSON::Load(chunk6_json);
					for (int y = 25; y < 30; y++)
					{
						for (int x = 0; x < 120; x++)
						{
							game->de->DrawSinglePixel(static_cast<char>(chunk6[y][x].ToInt()), x, y);
						}
					}
				}

				if (GetConsoleWindow() == GetForegroundWindow())
				{
					if (GetAsyncKeyState(VK_ESCAPE)) { breaker = true; break; }
					else if (GetAsyncKeyState(0x57/*W*/) || GetAsyncKeyState(VK_UP))
						game->MovePlayerUp();
					else if (GetAsyncKeyState(0x41/*A*/) || GetAsyncKeyState(VK_LEFT))
						game->MovePlayerLeft();
					else if (GetAsyncKeyState(0x53/*S*/) || GetAsyncKeyState(VK_DOWN))
						game->MovePlayerDown();
					else if (GetAsyncKeyState(0x44/*D*/) || GetAsyncKeyState(VK_RIGHT))
						game->MovePlayerRight();
				}
				std::string setplayers = "setPlayer " + std::to_string(game->GetPlayerX()) + " " + std::to_string(game->GetPlayerY()) + " " + cha;
				peer->Send((char*)setplayers.c_str(), strlen(setplayers.c_str()) + 1, HIGH_PRIORITY, RELIABLE, 0, packet->systemAddress, false);

				game->de->Draw();
			}
			if (breaker)break;
		}

		RakNet::RakPeerInterface::DestroyInstance(peer);
	}
	std::cout << std::endl << std::endl;
	system("pause");
	delete game;
	return 0;
}