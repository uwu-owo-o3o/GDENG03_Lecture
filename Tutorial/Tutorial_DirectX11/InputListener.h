#pragma once
#include "Point.h"

class InputListener 
{
	public:
		InputListener() 
		{

		}

		~InputListener()
		{

		}

		virtual void OnKeyDown(int key) = 0;
		virtual void OnKeyUp(int key) = 0;

		virtual void OnMouseMove(const Point& deltaMousePos) = 0;

};