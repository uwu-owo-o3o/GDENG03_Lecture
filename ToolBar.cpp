#include "ToolBar.h"
#include "UIManager.h"

ToolBar::ToolBar(float width, float height)
{
	this->screenWidth = width;
	this->screenHeight = height;
	this->screenName = "Tool Bar";
	this->isOpen = true;
}

ToolBar::~ToolBar()
{
}

void ToolBar::draw()
{

	ImGui::SetNextWindowSize(ImVec2(screenWidth, 50));
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::Begin("Tool Bar");;

	this->drawAboutButton();
	this->drawColorPickerButton();
	
	ImGui::End();
}

void ToolBar::drawAboutButton()
{
	if (ImGui::Button("About")) {
		CreditsScreen* creditsScreen = (CreditsScreen*)UIManager::findScreen("Credits Screen");
		
		if (creditsScreen == nullptr) return;

		if (creditsScreen->isOpen) {
			creditsScreen->isOpen = false;
		}
		else {
			creditsScreen->isOpen = true;
		}
	}
}

void ToolBar::drawColorPickerButton()
{
	ImGui::SameLine();
	ImGui::PushItemWidth(10);
	if (ImGui::Button("Color Picker")) {
		ColorPickerScreen* colorPickerScreen = (ColorPickerScreen*)UIManager::findScreen("Color Picker Screen");

		if (colorPickerScreen == nullptr) return;

		if (colorPickerScreen->isOpen) {
			colorPickerScreen->isOpen = false;
		}
		else {
			colorPickerScreen->isOpen = true;
		}
	}
}
