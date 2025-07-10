#pragma once
#include "UIScreen.h"
#include "UIImage.h"

class CreditsScreen : public UIScreen
{
	public:
		CreditsScreen(float width, float height);
		~CreditsScreen();

	public:
		virtual void draw() override;

	public:
		UIImage dlsu_logo;

};

