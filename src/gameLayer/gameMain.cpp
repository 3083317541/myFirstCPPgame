#include <raylib.h>
#include "gameMain.h"
#include <asserts.h>

struct GameDate
{

	float positionX = 100;
	float positionY = 100;

}gameData;

bool initGame()
{
	return true;
}

bool updateGame()
{
	float deltaTime = GetFrameTime();
	if (deltaTime > 1.f / 5) { deltaTime = 1 / 5.f; }

	if (IsKeyDown(KEY_A)) { gameData.positionX -= 1; }
	if (IsKeyDown(KEY_D)) { gameData.positionX += 1; }
	if (IsKeyDown(KEY_W)) { gameData.positionY -= 1; }
	if (IsKeyDown(KEY_S)) { gameData.positionY += 1; }

	DrawRectangle(gameData.positionX, gameData.positionY, 50, 50, c);

	return true;
}

void closeGame()
{

}