#pragma once

#include <iostream>
#include <chrono>
#include <ctime>
class Window;

class EngineTime
{
	public:
		static void initialize();
		static double getDeltaTime();
		
		static int id;
	private:
		EngineTime();
		~EngineTime();
		EngineTime& operator=(EngineTime const&) {};

		static EngineTime* sharedInstance;
		
	private:
		std::chrono::system_clock::time_point start;
		std::chrono::system_clock::time_point end;

		double deltaTime = 0.0f;

		static void LogFrameStart();
		static void LogFrameEnd();

		friend class Window;

};

