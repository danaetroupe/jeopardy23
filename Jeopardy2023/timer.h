#pragma once
#include <SDL.h>
class Timer
{
public:
	Timer(Uint32 seconds);
	~Timer();

	void start();
	void stop();
	//void pause();
	//void restart();

	Uint32 getTime();
protected:
	Uint32 initTime;
	Uint32 timeRemaining;
	bool isTicking = false;
};

