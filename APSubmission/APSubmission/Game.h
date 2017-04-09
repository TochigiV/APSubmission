#pragma once

//todo: make character detect walls

class Game
{
private:
	int playerX;
	int playerY;
	char prevChar;
	char playerChar;
public:
	int GetPlayerX() { return playerX; }
	int GetPlayerY() { return playerY; }
	void SpawnPlayer(char letter, int x, int y);
	void MovePlayerUp();
	void MovePlayerDown();
	void MovePlayerLeft();
	void MovePlayerRight();
};