#include "Game.h"

Game::Game(wchar_t letter, int x, int y)
{
	drawEngine = new DrawEngine();
	if (drawEngine->GetChar(x, y) != '+')
	{
		playerX = x;
		playerY = y;
		prevChar = drawEngine->GetChar(x, y);
		playerChar = letter;
		drawEngine->DrawSinglePixel(playerChar, playerX, playerY);
	}
	else Game(letter, (x + 1), (y + 1));
}

Game::~Game()
{
	delete drawEngine;
}

void Game::SetWallCharacter(wchar_t wallChar)
{
	wallChars = wallChar;
}

void Game::SetPlayerCharacter(wchar_t pChar)
{
	playerChar = pChar;
}

void Game::MovePlayerUp()
{
	if (playerY != 0 && drawEngine->GetChar(playerX, (playerY - 1)) != wallChars)
	{
		drawEngine->DrawSinglePixel(prevChar, playerX, playerY);
		playerY--;
		prevChar = drawEngine->GetChar(playerX, playerY);
		if (prevChar == '#') { score++; prevChar = ' '; }
		drawEngine->DrawSinglePixel(playerChar, playerX, playerY);
	}
}

void Game::MovePlayerDown()
{
	if (playerY != (drawEngine->GetRows() - 1) && drawEngine->GetChar(playerX, (playerY + 1)) != wallChars)
	{
		drawEngine->DrawSinglePixel(prevChar, playerX, playerY);
		playerY++;
		prevChar = drawEngine->GetChar(playerX, playerY);
		if (prevChar == '#') { score++; prevChar = ' '; }
		drawEngine->DrawSinglePixel(playerChar, playerX, playerY);
	}
}

void Game::MovePlayerLeft()
{
	if (playerX != 0 && drawEngine->GetChar((playerX - 1), playerY) != wallChars)
	{
		drawEngine->DrawSinglePixel(prevChar, playerX, playerY);
		playerX--;
		prevChar = drawEngine->GetChar(playerX, playerY);
		if (prevChar == '#') { score++; prevChar = ' '; }
		drawEngine->DrawSinglePixel(playerChar, playerX, playerY);
	}
}

void Game::MovePlayerRight()
{
	if (playerX != (drawEngine->GetColumns() - 1) && drawEngine->GetChar((playerX + 1), playerY) != wallChars)
	{
		drawEngine->DrawSinglePixel(prevChar, playerX, playerY);
		playerX++;
		prevChar = drawEngine->GetChar(playerX, playerY);
		if (prevChar == '#') { score++; prevChar = ' '; }
		drawEngine->DrawSinglePixel(playerChar, playerX, playerY);
	}
}
