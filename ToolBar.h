#pragma once
#include "UIScreen.h"

class ToolBar : public UIScreen
{
	public:
		ToolBar(float width, float height);
		~ToolBar();

	public:
		virtual void draw() override;

	private:
		void drawAboutButton();
		void drawColorPickerButton();
		void drawSpawnButton();
};

