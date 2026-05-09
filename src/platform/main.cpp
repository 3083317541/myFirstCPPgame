#include <iostream>
#include <raylib.h>
#include <imgui.h>
#include <rlImGui.h>
#include <gameMain.h>

int main()
{

#if PRODUCTION_BUILD == 1
	SetTraceLogLevel(LOG_NONE);
#endif


	//设置窗口标志(允许窗口拖拽缩放)
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	//初始化窗口(宽度， 高度， 标题)
	InitWindow(800, 450, "window name");
	SetExitKey(KEY_NULL);
	SetTargetFPS(240);

#pragma region imgui
	rlImGuiSetup(true);

	ImGuiIO& io = ImGui::GetIO();	//获取ImGui的全局输出配置对象

	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;	//开启窗口停靠/标签页
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; //允许键盘控制
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  //允许手柄控制

	io.FontGlobalScale = 1.5f;	//全局字体缩放
#pragma endregion

	if (!initGame())
	{
		return 0;
	}

	while (!WindowShouldClose())
	{

		BeginDrawing();

		ClearBackground(BLACK);

		if (!updateGame())
		{
			CloseWindow();
		}

#pragma region imgui

		rlImGuiBegin();

		//停靠附件
		ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		ImGui::PopStyleColor(2);

		rlImGuiEnd();

#pragma endregion

		EndDrawing();
	}

	CloseWindow();

	closeGame();

#pragma region imgui
	rlImGuiShutdown();
#pragma endregion

}