#pragma once

#include "DrawEngine.h"

class Game
{
private:
	int playerX;
	int playerY;
	wchar_t prevChar;
	wchar_t playerChar;
	wchar_t wallChars;
public:
	DrawEngine *drawEngine;
	int score = 0;
	Game(wchar_t letter, int x, int y);
	~Game();
	int GetPlayerX() { return playerX; }
	int GetPlayerY() { return playerY; }
	void SetWallCharacter(wchar_t wallChar);
	void SetPlayerCharacter(wchar_t pChar);
	void MovePlayerUp();
	void MovePlayerDown();
	void MovePlayerLeft();
	void MovePlayerRight();
};