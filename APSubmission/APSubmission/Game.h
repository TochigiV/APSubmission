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
	int score = 0;
	Game(char letter, int x, int y);
	~Game();
	int GetPlayerX() { return playerX; }
	int GetPlayerY() { return playerY; }
	void SetWallCharacter(char wallChar);
	void MovePlayerUp();
	void MovePlayerDown();
	void MovePlayerLeft();
	void MovePlayerRight();
};