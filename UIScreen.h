#pragma once
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "imgui.h"
#include "string"

class UIScreen {
	public:
		virtual void draw() = 0;

	protected:
		float screenWidth;
		float screenHeight;
		bool isOpen;

	public:
		std::string screenName;
};