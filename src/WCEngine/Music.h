#ifndef MUSIC_H
#define MUSIC_H

#include <string>
#include <SDL/SDL_mixer.h>

namespace gdn
{
	class Music
	{
		public:
			Music();
			virtual ~Music();

			bool LoadFromFile( std::string filename );
			void SetLoop( bool on );

			bool IsPlaying();
			void Play();
			void Stop();

		protected:
			Mix_Music* buffer;
			bool isLoop;

			static Music* currentlyPlaying;

		private:
	};
}

#endif // MUSIC_H
