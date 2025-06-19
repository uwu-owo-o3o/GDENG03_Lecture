#pragma once
#include <Windows.h>

class Window
{
	public:
		Window();
		bool broadcast();
		~Window();

		bool isRun();

		RECT getClientWindowRect();

		//Event Functions
		virtual void onCreate() = 0;
		virtual void onUpdate();
		virtual void onDestroy();

		virtual void onFocus();
		virtual void onKillFocus();
	protected:
		HWND m_hwnd;
		bool m_isRun;
		bool m_is_init = false;

};

