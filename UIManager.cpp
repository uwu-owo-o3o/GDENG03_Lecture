#include "UIManager.h"

UIManager* UIManager::sharedInstance = nullptr;
bool UIManager::showWindow = true;

void UIManager::initialize(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* device_context)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(device, device_context);

	if (sharedInstance == nullptr) {
		sharedInstance = new UIManager();
	}
}

void UIManager::update()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Credits", &showWindow);                          
	ImGui::Text("Scene Editor Version 1.0.0     ");
	ImGui::Text("Developed by: Lance Ong        ");

	if (ImGui::Button("Close")) {
		std::cout << "clicked!" << std::endl;
	}

	ImGui::End();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}



UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}
