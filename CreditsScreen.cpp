#include "CreditsScreen.h"

CreditsScreen::CreditsScreen(float width, float height)
{
	this->dlsu_logo = UIImage(0, 0, 0.15);
	this->dlsu_logo.createImage();
}

CreditsScreen::~CreditsScreen()
{
}

void CreditsScreen::draw()
{
	ImGui::Begin("Credits");;
	
	this->dlsu_logo.drawImage();

	ImGui::End();
}
