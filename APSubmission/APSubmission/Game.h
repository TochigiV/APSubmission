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
	Game(char letter, int x, int y);
	int GetPlayerX() { return playerX; }
	int GetPlayerY() { return playerY; }
	void AddWallCharacters(std::vector<char> wallChar);
	void MovePlayerUp();
	void MovePlayerDown();
	void MovePlayerLeft();
	void MovePlayerRight();
};