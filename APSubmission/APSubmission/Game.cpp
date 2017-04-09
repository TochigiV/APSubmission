#include "Game.h"
#include "DrawEngine.h"

void Game::SpawnPlayer(char letter, int x, int y)
{
	playerX = x;
	playerY = y;
	prevChar = de->GetLetter(x, y);
	playerChar = letter;
	de->DrawSinglePixel(playerChar, playerX, playerY);
	//de->Draw();
}

void Game::MovePlayerUp()
{
	de->DrawSinglePixel(prevChar, playerX, playerY);
	playerY--;
	prevChar = de->GetLetter(playerX, playerY);
	de->DrawSinglePixel(playerChar, playerX, playerY);
	//de->Draw();
}

void Game::MovePlayerDown()
{
	de->DrawSinglePixel(prevChar, playerX, playerY);
	playerY++;
	prevChar = de->GetLetter(playerX, playerY);
	de->DrawSinglePixel(playerChar, playerX, playerY);
	//de->Draw();
}

void Game::MovePlayerLeft()
{
	de->DrawSinglePixel(prevChar, playerX, playerY);
	playerX--;
	prevChar = de->GetLetter(playerX, playerY);
	de->DrawSinglePixel(playerChar, playerX, playerY);
	//de->Draw();
}

void Game::MovePlayerRight()
{
	de->DrawSinglePixel(prevChar, playerX, playerY);
	playerX++;
	prevChar = de->GetLetter(playerX, playerY);
	de->DrawSinglePixel(playerChar, playerX, playerY);
	//de->Draw();
}