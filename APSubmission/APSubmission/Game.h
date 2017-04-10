#pragma once

#include "DrawEngine.h"

class Game
{
private:
	int playerX;
	int playerY;
	char prevChar;
	char playerChar;
	std::vector<char> wallChars;
public:
	DrawEngine *de;
	Game();
	int GetPlayerX() { return playerX; }
	int GetPlayerY() { return playerY; }
	void SpawnPlayer(char letter, int x, int y);
	void AddWallCharacters(std::vector<char> wallChar);
	void MovePlayerUp();
	void MovePlayerDown();
	void MovePlayerLeft();
	void MovePlayerRight();
};