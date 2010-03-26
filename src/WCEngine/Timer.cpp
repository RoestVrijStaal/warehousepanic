#include "Timer.h"



namespace gdn
{
	Timer::Timer() : startTick( SDL_GetTicks() )
	{
	}

	Timer::~Timer()
	{
	}

	float Timer::GetElapsedTime()
	{
		Uint32 diff = SDL_GetTicks() - startTick;
		return (float)diff / 1000.0f;
	}

	void Timer::Reset()
	{
		startTick = SDL_GetTicks();
	}
}
