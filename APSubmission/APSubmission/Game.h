#pragma once

#include "DrawEngine.h"

class Game
{
private:
	int playerX;
	int playerY;
	char prevChar;
	char playerChar;
	char wallChars;
public:
	DrawEngine *de;
	Game(char letter, int x, int y);
	int GetPlayerX() { return playerX; }
	int GetPlayerY() { return playerY; }
	void SetWallCharacter(char wallChar);
	void MovePlayerUp();
	void MovePlayerDown();
	void MovePlayerLeft();
	void MovePlayerRight();
};