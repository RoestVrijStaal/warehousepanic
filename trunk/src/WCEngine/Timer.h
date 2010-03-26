#ifndef TIMER_H
#define TIMER_H


#include <SDL/SDL.h>

namespace gdn
{
	class Timer
	{
		public:
			Timer();
			virtual ~Timer();

			float GetElapsedTime();
			void Reset();
		protected:
		private:
		Uint32 startTick;
	};
}

#endif // TIMER_H
