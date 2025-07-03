#pragma once
#include "iostream"
#include <Windows.h>
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "imgui.h"

class UIManager
{
	public:
		static void initialize(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* device_context);
		static void update();

		static bool showWindow;

	private:
		UIManager();
		~UIManager();
		UIManager& operator=(UIManager const&) {};

		static UIManager* sharedInstance;

};

