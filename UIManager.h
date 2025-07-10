#pragma once
#include "iostream"
#include <Windows.h>
#include "vector"
#include "UIScreen.h"
#include "ToolBar.h"
#include "CreditsScreen.h"

class UIManager
{
	public:
		static void initialize(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* device_context);
		static void draw();
		static void addScreen(UIScreen* screen);

	private:
		UIManager();
		~UIManager();
		UIManager& operator=(UIManager const&) {};

		static UIManager* sharedInstance;

	private:
		static std::vector<UIScreen*> uiScreens;
};

