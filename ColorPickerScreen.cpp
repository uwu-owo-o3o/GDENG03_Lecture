#include "ColorPickerScreen.h"

ColorPickerScreen::ColorPickerScreen(float width, float height)
{
	this->screenName = "Color Picker Screen";
	this->isOpen = false;
	this->screenWidth = width;
	this->screenHeight = height;
}

ColorPickerScreen::~ColorPickerScreen()
{
}

void ColorPickerScreen::draw()
{
	if (this->isOpen) {
		ImGui::SetNextWindowSize(ImVec2(500, 350));
		ImGui::SetNextWindowPos(ImVec2(0, 60));
		ImGui::Begin("Color Picker");
		ImGui::ColorPicker4("Color Picker Tool", color, 
							ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_PickerHueWheel | 
							ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs);
		ImGui::End();
	}
}
