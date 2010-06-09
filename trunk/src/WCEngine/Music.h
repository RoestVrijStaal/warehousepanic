#ifndef MUSIC_H
#define MUSIC_H

#include <string>

#if defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)
#include <SDL_mixer/SDL_mixer.h>
#else
#include <SDL/SDL_mixer.h>
#endif

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
