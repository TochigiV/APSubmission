#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <conio.h>
#include <sstream> 
#include <ostream>
#include <iterator>
#include <algorithm> 

#include <Windows.h>

#include "..\RakNet\RakPeerInterface.h"
#include "..\RakNet\MessageIdentifiers.h"
#include "..\RakNet\BitStream.h"
#include "..\RakNet\RakNetTypes.h"

#include "json.hpp"

#pragma comment(lib, "Ws2_32.lib")

//#define USE_SYS

#ifndef USE_SYS
#define pause std::cout << "Press any key to continue . . . " << std::endl; _getch
#else
#define pause() system("pause")
#endif

std::vector<std::string> split(std::string s) {
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);
	return vstrings;
}

CONSOLE_SCREEN_BUFFER_INFO csbi;
HANDLE stdHandle;
int columns, rows;
char cmap[30][120];
int prevx = 0, prevy = 0, cx = 0, cy = 0;
char prevchar = ' ';

void FillMap(char c)
{
	for (int y = 0; y < 30; y++)
		for (int x = 0; x < 120; x++)
			cmap[y][x] = c;
}


void cls()
{
	COORD topLeft = { 0, 0 };
	DWORD length = csbi.dwSize.X * csbi.dwSize.Y;
	DWORD written;
	std::cout.flush();
	FillConsoleOutputCharacter(stdHandle, L' ', length, topLeft, &written);
	FillConsoleOutputAttribute(stdHandle, csbi.wAttributes, length, topLeft, &written);
	SetConsoleCursorPosition(stdHandle, topLeft);
}

int main()
{
	setvbuf(stdout, NULL, _IOFBF, 512);
	SetConsoleTitle("APSubmission-server");

	stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(stdHandle, &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	COORD NewSBSize = { (SHORT)columns, (SHORT)rows };
	SetConsoleScreenBufferSize(stdHandle, NewSBSize);

	WIN32_FIND_DATA fdata;
	if (FindFirstFile("server.json", &fdata) != INVALID_HANDLE_VALUE)
	{
		std::ifstream ifs("server.json");
		if (ifs.is_open())
		{
			std::string jsonc((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
			json::JSON obj = json::JSON::Load(jsonc.c_str());

			std::string ip;
			int port;
			bool isdone;

			if (obj.hasKey("ip") && obj.hasKey("port") && obj.hasKey("config_complete"))
			{
				ip = obj["ip"].ToString();
				port = obj["port"].ToInt();
				isdone = obj["config_complete"].ToBool();
			}
			else
			{
				std::cout << "Error finding children!" << std::endl;
				pause();
				return 0;
			}

			if (isdone)
			{

				std::cout << "Statring server on IP: " << ip << ", PORT: " << port << std::endl;
				std::string contitle = "APSubmission-server IP: " + ip + " PORT: " + std::to_string(port);
				SetConsoleTitle(contitle.c_str());
				RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance();
				RakNet::Packet *packet;

				peer->Startup(10, &RakNet::SocketDescriptor(port, ip.c_str()), 1);
				peer->SetMaximumIncomingConnections(10);

				FillMap('+');

				while (1)
				{
					//CHUNK 1
					json::JSON chunk1;
					for (int y = 0; y < 5; y++)
					{
						chunk1[y] = json::Object();
						for (int x = 0; x < 120; x++)
						{
							chunk1[y][x] = cmap[y][x];
						}
					}
					std::string chunk1_s;
					chunk1_s += "1";
					chunk1_s += chunk1.dump();

					//CHUNK 2
					json::JSON chunk2;
					for (int y = 5; y < 10; y++)
					{
						chunk2[y] = json::Object();
						for (int x = 0; x < 120; x++)
						{
							chunk2[y][x] = cmap[y][x];
						}
					}
					std::string chunk2_s;
					chunk2_s += "2";
					chunk2_s += chunk2.dump();

					//CHUNK 3
					json::JSON chunk3;
					for (int y = 10; y < 15; y++)
					{
						chunk3[y] = json::Object();
						for (int x = 0; x < 120; x++)
						{
							chunk3[y][x] = cmap[y][x];
						}
					}
					std::string chunk3_s;
					chunk3_s += "3";
					chunk3_s += chunk3.dump();

					//CHUNK 4
					json::JSON chunk4;
					for (int y = 15; y < 20; y++)
					{
						chunk4[y] = json::Object();
						for (int x = 0; x < 120; x++)
						{
							chunk4[y][x] = cmap[y][x];
						}
					}
					std::string chunk4_s;
					chunk4_s += "4";
					chunk4_s += chunk4.dump();

					//CHUNK 5
					json::JSON chunk5;
					for (int y = 20; y < 25; y++)
					{
						chunk5[y] = json::Object();
						for (int x = 0; x < 120; x++)
						{
							chunk5[y][x] = cmap[y][x];
						}
					}
					std::string chunk5_s;
					chunk5_s += "5";
					chunk5_s += chunk5.dump();

					//CHUNK 6
					json::JSON chunk6;
					for (int y = 25; y < 30; y++)
					{
						chunk6[y] = json::Object();
						for (int x = 0; x < 120; x++)
						{
							chunk6[y][x] = cmap[y][x];
						}
					}
					std::string chunk6_s;
					chunk6_s += "6";
					chunk6_s += chunk6.dump();

					peer->Send((char*)chunk1_s.c_str(), strlen(chunk1_s.c_str()) + 1, HIGH_PRIORITY, RELIABLE, 0, RakNet::UNASSIGNED_RAKNET_GUID, true);
					peer->Send((char*)chunk2_s.c_str(), strlen(chunk2_s.c_str()) + 1, HIGH_PRIORITY, RELIABLE, 0, RakNet::UNASSIGNED_RAKNET_GUID, true);
					peer->Send((char*)chunk3_s.c_str(), strlen(chunk3_s.c_str()) + 1, HIGH_PRIORITY, RELIABLE, 0, RakNet::UNASSIGNED_RAKNET_GUID, true);
					peer->Send((char*)chunk4_s.c_str(), strlen(chunk4_s.c_str()) + 1, HIGH_PRIORITY, RELIABLE, 0, RakNet::UNASSIGNED_RAKNET_GUID, true);
					peer->Send((char*)chunk5_s.c_str(), strlen(chunk5_s.c_str()) + 1, HIGH_PRIORITY, RELIABLE, 0, RakNet::UNASSIGNED_RAKNET_GUID, true);
					peer->Send((char*)chunk6_s.c_str(), strlen(chunk6_s.c_str()) + 1, HIGH_PRIORITY, RELIABLE, 0, RakNet::UNASSIGNED_RAKNET_GUID, true);

					for (packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive())
					{
						std::string packetstring;
						for (int i = 0; i < packet->length; i++)
							packetstring += packet->data[i];

						std::vector<std::string>splitstr = split(packetstring);

						if (splitstr[0] == "setPlayer")
						{
							if (std::stoi(splitstr[1]) != cx && std::stoi(splitstr[2]) != cy)
							{
								cmap[prevy][prevx] = prevchar;
								int x = std::stoi(splitstr[1]);
								int y = std::stoi(splitstr[2]);
								const char* pchar = splitstr[3].c_str();
								prevx = x;
								prevy = y;
								prevchar = cmap[y][x];


								cmap[y][x] = pchar[0];
								cx = x;
								cy = y;
							}
						}
					}

					cls();
					for (int y = 0; y < 30; y++)
					{
						for (int x = 0; x < 120; x++)
						{
							std::cout << cmap[y][x];
						}
					}

					if (GetConsoleWindow() == GetForegroundWindow())
						if (GetAsyncKeyState(VK_ESCAPE)) break;
					Sleep(100);
				}
				peer->Shutdown(300);
				RakNet::RakPeerInterface::DestroyInstance(peer);
			}
			else
			{
				std::cout << "Setup not complete! If you are done configuring 'server.json,' set 'config_complete' to true." << std::endl;
			}
		}
		else
		{
			std::cout << "Unable to open server.json!" << std::endl;
		}
	}
	else
	{
		std::ofstream ofs("server.json");
		ofs << "{\n\t\"ip\": \"\",\n\t\"port\": 27015,\n\t\"config_complete\": false\n}" << std::endl;
		ofs.close();
		std::cout << "Created file 'server.json,' please edit it before trying to run a server!" << std::endl;
	}
	pause();
	return 0;
}
