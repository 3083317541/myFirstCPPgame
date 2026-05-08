#include <raylib.h>
#include "gameMain.h"

bool initGame()
{
	return true;
}

bool updateGame()
{
	Color c;
	c.r = 255;
	c.g = 0;
	c.b = 200;
	c.a = 255;

	//绘制文本(~, X坐标，Y坐标，字体大小，颜色)
	DrawText("Congrats! You created your first window!", 190, 200, 20, c);


	return true;
}

void closeGame()
{

}