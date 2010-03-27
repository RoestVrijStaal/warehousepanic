#ifndef SOUNDBUFFER_H
#define SOUNDBUFFER_H

#include <string>

class Mix_Chunk;

namespace gdn
{
	class SoundBuffer
	{
		public:
			SoundBuffer();
			virtual ~SoundBuffer();

			bool LoadFromFile( std::string filename );
			Mix_Chunk* GetBuffer();

		protected:
			Mix_Chunk* buffer;
		private:
	};
}

#endif // SOUNDBUFFER_H
