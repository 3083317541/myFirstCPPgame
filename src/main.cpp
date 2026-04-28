#include <iostream>
#include <raylib.h>
#include <imgui.h>
#include <rlImGui.h>

int main()
{
	
	//设置窗口标志(允许窗口拖拽缩放)
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	//初始化窗口(宽度， 高度， 标题)
	InitWindow(800, 450, "window name");

#pragma region imgui
	rlImGuiSetup(true);	//rlimgui初始化

	ImGuiIO& io = ImGui::GetIO();	//获取ImGui的全局输出配置对象
	
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;	//开启窗口停靠/标签页
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; //允许键盘控制
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  //允许手柄控制

	io.FontGlobalScale = 2.5;	//全局字体缩放
#pragma endregion

	//主循环
	while (!WindowShouldClose())
	{

		//开始绘制
		BeginDrawing();
		//清空背景(背景颜色为灰色)
		ClearBackground(RAYWHITE);
#pragma region imgui
		rlImGuiBegin();

		//停靠附件
		ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		ImGui::PopStyleColor(2);

#pragma endregion

		Color c;
		c.r = 255; //红
		c.g = 0;   //绿
		c.b = 200; //蓝
		c.a = 255; //不透明度

		//绘制文本(~, X坐标，Y坐标，字体大小，颜色)
		DrawText("Congrats! You created your first window!", 190, 200, 20, /*c*/
			{255, 0, 200, 255}
			);

#pragma region imgui windows
		ImGui::Begin("First"); //同名窗口合并
		ImGui::Text("Hello");

		ImGui::PushID(1); //压入ID1
		if (ImGui::Button("button")) //控件不能有相同ID,##标签区分
		{
			std::cout << "Button 1" << std::endl;
		}
		ImGui::PopID();	  //弹出ID1

		ImGui::SameLine();

		ImGui::PushID(2); //压入ID2
		if (ImGui::Button("button"))
		{
			std::cout << "Button 2" << std::endl;
		}
		ImGui::PopID();  //弹出ID2

		ImGui::End();

		ImGui::Begin("Second");
		ImGui::Separator(); //分隔符
		ImGui::NewLine();
		static float a = 0;
		ImGui::SliderFloat("slider", &a, 0, 1); //滑块
		ImGui::End();
#pragma endregion

#pragma region imgui
		//rlimgui结束调用
		rlImGuiEnd();
#pragma endregion

		//结束绘制
		EndDrawing();
	}
	
#pragma region imgui
	//rlimgui结束
	rlImGuiShutdown();
#pragma endregion

	//关闭窗口，释放内存
	CloseWindow();

}