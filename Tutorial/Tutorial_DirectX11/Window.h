#pragma once
#include <Windows.h>

class Window
{
	public:
		Window();
		bool init(); // initialize the window
		bool broadcast();
		bool release(); // release or destroy the window
		~Window();

		bool isRun();

		RECT getClientWindowRect();
		void setHWND(HWND hwnd);

		//Event Functions
		virtual void onCreate() = 0;
		virtual void onUpdate();
		virtual void onDestroy();

		virtual void onFocus();
		virtual void onKillFocus();
	protected:
		HWND m_hwnd;
		bool m_isRun;

};

