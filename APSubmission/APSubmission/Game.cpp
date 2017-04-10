#include "Game.h"

//+ = wall

Game::Game()
{
	de = new DrawEngine();
}

void Game::SpawnPlayer(char letter, int x, int y)
{
	if (de->GetLetter(x, y) != '+')
	{
		playerX = x;
		playerY = y;
		prevChar = de->GetLetter(x, y);
		playerChar = letter;
		de->DrawSinglePixel(playerChar, playerX, playerY);
	}
	else SpawnPlayer(letter, (x + 1), (y + 1)); //this will recurse until it gets to a point that isn't a wall
}

void Game::AddWallCharacters(std::vector<char> wallChar)
{
	for(int i = 0; i < wallChar.size(); i++)
		wallChars.push_back(wallChar[i]);
}

void Game::MovePlayerUp()
{
	if (playerY != 0 && de->GetLetter(playerX, (playerY - 1)) != '+')
	{
		de->DrawSinglePixel(prevChar, playerX, playerY);
		playerY--;
		prevChar = de->GetLetter(playerX, playerY);
		de->DrawSinglePixel(playerChar, playerX, playerY);
	}
}

void Game::MovePlayerDown()
{
	if (playerY != 29 && de->GetLetter(playerX, (playerY + 1)) != '+')
	{
		de->DrawSinglePixel(prevChar, playerX, playerY);
		playerY++;
		prevChar = de->GetLetter(playerX, playerY);
		de->DrawSinglePixel(playerChar, playerX, playerY);
	}
}

void Game::MovePlayerLeft()
{
	if (playerX != 0 && de->GetLetter((playerX - 1), playerY) != '+')
	{
		de->DrawSinglePixel(prevChar, playerX, playerY);
		playerX--;
		prevChar = de->GetLetter(playerX, playerY);
		de->DrawSinglePixel(playerChar, playerX, playerY);
	}
}

void Game::MovePlayerRight()
{
	if (playerX != 119 && de->GetLetter((playerX + 1), playerY) != '+')
	{
		de->DrawSinglePixel(prevChar, playerX, playerY);
		playerX++;
		prevChar = de->GetLetter(playerX, playerY);
		de->DrawSinglePixel(playerChar, playerX, playerY);
	}
}