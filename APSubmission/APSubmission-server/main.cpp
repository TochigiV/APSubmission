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

char cmap[50][50];

int main()
{
	SetConsoleTitle("APSubmission-server");
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
				RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance();
				RakNet::Packet *packet;

				peer->Startup(10, &RakNet::SocketDescriptor(port, ip.c_str()), 1);
				peer->SetMaximumIncomingConnections(10);
				while (1)
				{

					//CHUNK 1
					json::JSON chunk1;
					for (int y = 0; y < 5; y++)
					{
						chunk1[y] = json::Object();
						for (int x = 0; x < 120; x++)
						{
							cmap[y][x] = '*';
							chunk1[y][x] = cmap[y][x];
						}
					}
					std::string chunk1_s;
					chunk1_s += "201";
					chunk1_s += chunk1.dump();

					//CHUNK 2
					json::JSON chunk2;
					for (int y = 5; y < 10; y++)
					{
						chunk2[y] = json::Object();
						for (int x = 0; x < 120; x++)
						{
							cmap[y][x] = '*';
							chunk2[y][x] = cmap[y][x];
						}
					}
					std::string chunk2_s;
					chunk2_s += "202";
					chunk2_s += chunk2.dump();

					//CHUNK 3
					json::JSON chunk3;
					for (int y = 10; y < 15; y++)
					{
						chunk3[y] = json::Object();
						for (int x = 0; x < 120; x++)
						{
							cmap[y][x] = '*';
							chunk3[y][x] = cmap[y][x];
						}
					}
					std::string chunk3_s;
					chunk3_s += "203";
					chunk3_s += chunk3.dump();

					//CHUNK 4
					json::JSON chunk4;
					for (int y = 15; y < 20; y++)
					{
						chunk4[y] = json::Object();
						for (int x = 0; x < 120; x++)
						{
							cmap[y][x] = '*';
							chunk4[y][x] = cmap[y][x];
						}
					}
					std::string chunk4_s;
					chunk4_s += "204";
					chunk4_s += chunk4.dump();

					//CHUNK 5
					json::JSON chunk5;
					for (int y = 20; y < 25; y++)
					{
						chunk5[y] = json::Object();
						for (int x = 0; x < 120; x++)
						{
							cmap[y][x] = '*';
							chunk5[y][x] = cmap[y][x];
						}
					}
					std::string chunk5_s;
					chunk5_s += "205";
					chunk5_s += chunk5.dump();

					//CHUNK 6
					json::JSON chunk6;
					for (int y = 25; y < 30; y++)
					{
						chunk6[y] = json::Object();
						for (int x = 0; x < 120; x++)
						{
							cmap[y][x] = '*';
							chunk6[y][x] = cmap[y][x];
						}
					}
					std::string chunk6_s;
					chunk6_s += "206";
					chunk6_s += chunk6.dump();


					peer->Send((char*)chunk1_s.c_str(), strlen(chunk1_s.c_str()) + 1, HIGH_PRIORITY, RELIABLE, 0, RakNet::UNASSIGNED_RAKNET_GUID, true);
					peer->Send((char*)chunk2_s.c_str(), strlen(chunk2_s.c_str()) + 1, HIGH_PRIORITY, RELIABLE, 0, RakNet::UNASSIGNED_RAKNET_GUID, true);
					peer->Send((char*)chunk3_s.c_str(), strlen(chunk3_s.c_str()) + 1, HIGH_PRIORITY, RELIABLE, 0, RakNet::UNASSIGNED_RAKNET_GUID, true);
					peer->Send((char*)chunk4_s.c_str(), strlen(chunk4_s.c_str()) + 1, HIGH_PRIORITY, RELIABLE, 0, RakNet::UNASSIGNED_RAKNET_GUID, true);
					peer->Send((char*)chunk5_s.c_str(), strlen(chunk5_s.c_str()) + 1, HIGH_PRIORITY, RELIABLE, 0, RakNet::UNASSIGNED_RAKNET_GUID, true);
					peer->Send((char*)chunk6_s.c_str(), strlen(chunk6_s.c_str()) + 1, HIGH_PRIORITY, RELIABLE, 0, RakNet::UNASSIGNED_RAKNET_GUID, true);

					if (GetConsoleWindow() == GetForegroundWindow())
						if (GetAsyncKeyState(VK_ESCAPE)) break;
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