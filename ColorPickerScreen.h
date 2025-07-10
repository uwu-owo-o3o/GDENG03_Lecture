#pragma once
#include "UIScreen.h"

class ColorPickerScreen : public UIScreen
{
	public:
		ColorPickerScreen(float width, float height);
		~ColorPickerScreen();

	public:
		virtual void draw() override;

	public:
		float color[3];
};

