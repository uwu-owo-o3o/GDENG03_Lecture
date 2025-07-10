#include "ToolBar.h"

ToolBar::ToolBar(float width, float height)
{
	this->screenWidth = width;
	this->screenHeight = height;
	this->screenName = "Tool Bar";
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

	}
}

void ToolBar::drawColorPickerButton()
{
	ImGui::SameLine();
	ImGui::PushItemWidth(10);
	if (ImGui::Button("Color Picker")) {

	}
}
