#include "AppWindow.h"


int main() 
{
	try {
		GraphicsEngine::create();
	}
	catch (...) { return -1; }

	try {
		AppWindow app;
		
		if (app.init()) {
			while (app.isRun()) { app.broadcast(); }
		}


	}
	catch (...) {}
	GraphicsEngine::release();

	return 0;
}