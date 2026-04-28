#include <iostream>
#include <raylib.h>

int main()
{
	
	//设置窗口标志(允许窗口拖拽缩放)
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	//初始化窗口(宽度， 高度， 标题)
	InitWindow(800, 450, "window name");

	//主循环
	while (!WindowShouldClose())
	{

		//开始绘制
		BeginDrawing();
		//清空背景(背景颜色为灰色)
		ClearBackground(RAYWHITE);

		Color c;
		c.r = 255; //红
		c.g = 0;   //绿
		c.b = 200; //蓝
		c.a = 255; //不透明度

		//绘制文本(~, X坐标，Y坐标，字体大小，颜色)
		DrawText("Congrats! You created your first window!", 190, 200, 20, /*c*/
			{255, 0, 200, 255}
			);

		//结束绘制
		EndDrawing();
	}
	
	//关闭窗口，释放内存
	CloseWindow();

}