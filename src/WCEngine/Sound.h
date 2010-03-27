#ifndef SOUND_H
#define SOUND_H

#include "SoundBuffer.h"

namespace gdn
{
	class Sound
	{
		public:
			Sound();
			Sound( SoundBuffer& newbuffer );
			virtual ~Sound();

			void Play();

		protected:
			SoundBuffer* buffer;
			int channel;

			// TODO: Make callback so this class can know when sample done playing
			// TODO: Store loop info etc.
		private:
	};
}

#endif // SOUND_H
