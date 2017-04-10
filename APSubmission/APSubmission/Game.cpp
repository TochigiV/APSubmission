#include "Game.h"

Game::Game(char letter, int x, int y)
{
	de = new DrawEngine();
	if (de->GetLetter(x, y) != '+')
	{
		playerX = x;
		playerY = y;
		prevChar = de->GetLetter(x, y);
		playerChar = letter;
		de->DrawSinglePixel(playerChar, playerX, playerY);
	}
	else Game(letter, (x + 1), (y + 1));
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