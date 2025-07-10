#include "UIManager.h"

UIManager* UIManager::sharedInstance = nullptr;
std::vector<UIScreen*> UIManager::uiScreens = std::vector<UIScreen*>();

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

	RECT rc;
	::GetClientRect(hwnd, &rc);

	float width = rc.right - rc.left;
	float height = rc.bottom - rc.top;

	ToolBar* toolBarScreen = new ToolBar(width, height);
	CreditsScreen* creditsScreen = new CreditsScreen(width, height);
	ColorPickerScreen* colorPickerScreen = new ColorPickerScreen(width, height);

	addScreen(toolBarScreen);
	addScreen(creditsScreen);
	addScreen(colorPickerScreen);
}

void UIManager::draw()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for (UIScreen* screen : uiScreens) {
		screen->draw();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void UIManager::addScreen(UIScreen* screen)
{
	uiScreens.push_back(screen);
}

UIScreen* UIManager::findScreen(std::string targetName)
{
	UIScreen* targetScreen = nullptr;
	for (UIScreen* screen : uiScreens) {
		if (screen->screenName == targetName) {
			targetScreen = screen;
		}
	}

	return targetScreen;
}



UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}
