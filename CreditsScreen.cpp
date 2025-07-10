#include "CreditsScreen.h"

CreditsScreen::CreditsScreen(float width, float height)
{
	this->screenName = "Credits Screen";
	this->dlsu_logo = UIImage(0, 0, 0.15);
	this->dlsu_logo.createImage();
	this->isOpen = false;
	this->screenWidth = width;
	this->screenHeight = height;
}

CreditsScreen::~CreditsScreen()
{
}

void CreditsScreen::draw()
{
	if (this->isOpen) {
		ImGui::SetNextWindowPos(ImVec2(0, 60));
		ImGui::Begin("Credits");;
		this->dlsu_logo.drawImage();
		this->writeDescription();
		ImGui::End();
	}
}

void CreditsScreen::writeDescription()
{
	ImGui::Text("About");
	ImGui::NewLine();

	ImGui::Text("Developed by: Lance D. Ong");
	ImGui::NewLine();

	ImGui::Text("Acknowledgements:");
	ImGui::Text("PardCode <3");
	ImGui::Text("Sir Neil's GDENG03 Course");
	ImGui::Text("imgui's ocornut");
	ImGui::Text("Coffee!!!");
}
