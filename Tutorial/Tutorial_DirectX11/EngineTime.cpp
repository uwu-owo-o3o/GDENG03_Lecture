#include "EngineTime.h"

EngineTime* EngineTime::sharedInstance = nullptr;
int EngineTime::id = 10;

EngineTime::EngineTime() {

}


void EngineTime::initialize()
{
	if (sharedInstance == nullptr) {
		sharedInstance = new EngineTime();
	}

	id = 12;
}

double EngineTime::getDeltaTime()
{
	return sharedInstance->deltaTime;
}

EngineTime::~EngineTime()
{
}

void EngineTime::LogFrameStart()
{
	sharedInstance->start = std::chrono::system_clock::now();
}

void EngineTime::LogFrameEnd()
{
	sharedInstance->end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = sharedInstance->end - sharedInstance->start;

	sharedInstance->deltaTime = elapsed_seconds.count();

	//std::cout << "Frame Update finished in: " << sharedInstance->deltaTime << std::endl;
}


