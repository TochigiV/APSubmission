/*
MIT License

Copyright (c) 2020 Bailey Brownie

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Game.h"

namespace DemoGame
{
	Game::Game(DrawEngine::gchar_t letter, int x, int y)
	{
		drawEngine = std::make_shared<DrawEngine::DrawEngine>();
		if (drawEngine->GetChar(x, y) != '+')
		{
			playerX = x;
			playerY = y;
			prevChar = drawEngine->GetChar(x, y);
			playerChar = letter;
			drawEngine->DrawPixel(playerChar, playerX, playerY, 10);
		}
		else Game(letter, (x + 1), (y + 1));
	}

	void Game::SetWallCharacter(DrawEngine::gchar_t wallChar)
	{
		wallChars = wallChar;
	}

	void Game::SetPlayerCharacter(DrawEngine::gchar_t pChar)
	{
		playerChar = pChar;
	}

	void Game::MovePlayerUp()
	{
		if (playerY != 0 && drawEngine->GetChar(playerX, (playerY - 1)) != wallChars)
		{
			drawEngine->DrawPixel(prevChar, playerX, playerY);
			playerY--;
			prevChar = drawEngine->GetChar(playerX, playerY);
			if (prevChar == '#') { score++; prevChar = ' '; }
			drawEngine->DrawPixel(playerChar, playerX, playerY, 10);
		}
	}

	void Game::MovePlayerDown()
	{
		if (playerY != (drawEngine->GetRows() - 1) && drawEngine->GetChar(playerX, (playerY + 1)) != wallChars)
		{
			drawEngine->DrawPixel(prevChar, playerX, playerY);
			playerY++;
			prevChar = drawEngine->GetChar(playerX, playerY);
			if (prevChar == '#') { score++; prevChar = ' '; }
			drawEngine->DrawPixel(playerChar, playerX, playerY, 10);
		}
	}

	void Game::MovePlayerLeft()
	{
		if (playerX != 0 && drawEngine->GetChar((playerX - 1), playerY) != wallChars)
		{
			drawEngine->DrawPixel(prevChar, playerX, playerY);
			playerX--;
			prevChar = drawEngine->GetChar(playerX, playerY);
			if (prevChar == '#') { score++; prevChar = ' '; }
			drawEngine->DrawPixel(playerChar, playerX, playerY, 10);
		}
	}

	void Game::MovePlayerRight()
	{
		if (playerX != (drawEngine->GetColumns() - 1) && drawEngine->GetChar((playerX + 1), playerY) != wallChars)
		{
			drawEngine->DrawPixel(prevChar, playerX, playerY);
			playerX++;
			prevChar = drawEngine->GetChar(playerX, playerY);
			if (prevChar == '#') { score++; prevChar = ' '; }
			drawEngine->DrawPixel(playerChar, playerX, playerY, 10);
		}
	}
}