#include "Game.h"
#include <time.h>

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

Game::~Game()
{
	delete de;
}

void Game::SetWallCharacter(char wallChar)
{
	wallChars = wallChar;
}

void Game::MovePlayerUp()
{
	if (playerY != 0 && de->GetLetter(playerX, (playerY - 1)) != wallChars)
	{
		de->DrawSinglePixel(prevChar, playerX, playerY);
		playerY--;
		prevChar = de->GetLetter(playerX, playerY);
		if (prevChar == '#') { score++; prevChar = ' '; }
		de->DrawSinglePixel(playerChar, playerX, playerY);
	}
}

void Game::MovePlayerDown()
{
	if (playerY != (de->GetRows() - 1) && de->GetLetter(playerX, (playerY + 1)) != wallChars)
	{
		de->DrawSinglePixel(prevChar, playerX, playerY);
		playerY++;
		prevChar = de->GetLetter(playerX, playerY);
		if (prevChar == '#') { score++; prevChar = ' '; }
		de->DrawSinglePixel(playerChar, playerX, playerY);
	}
}

void Game::MovePlayerLeft()
{
	if (playerX != 0 && de->GetLetter((playerX - 1), playerY) != wallChars)
	{
		de->DrawSinglePixel(prevChar, playerX, playerY);
		playerX--;
		prevChar = de->GetLetter(playerX, playerY);
		if (prevChar == '#') { score++; prevChar = ' '; }
		de->DrawSinglePixel(playerChar, playerX, playerY);
	}
}

void Game::MovePlayerRight()
{
	if (playerX != (de->GetColumns() - 1) && de->GetLetter((playerX + 1), playerY) != wallChars)
	{
		de->DrawSinglePixel(prevChar, playerX, playerY);
		playerX++;
		prevChar = de->GetLetter(playerX, playerY);
		if (prevChar == '#') { score++; prevChar = ' '; }
		de->DrawSinglePixel(playerChar, playerX, playerY);
	}
}