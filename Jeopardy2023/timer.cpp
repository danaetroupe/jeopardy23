#include "timer.h"
#include "stdio.h"
#include "iostream"
using namespace std;

Timer::Timer(Uint32 seconds) {
	initTime = 0;
	timeRemaining = seconds;
}

Timer::~Timer() {
	initTime = 0;
	timeRemaining = 0;
	isTicking = false;
}

void Timer::start() {
	isTicking = true;
	initTime = SDL_GetTicks();
}

Uint32 Timer::getTime() {
	if (isTicking) {
		Uint32 time = SDL_GetTicks() - initTime;
		Uint32 timeLeft = timeRemaining - (time / 1000);
		if (timeLeft <= 0) { 
			isTicking = false;
			return 0; 
		}
		else { return timeLeft; }
	}
	else {
		return 0;
	}
}

void Timer::stop() {
	isTicking = false;
}