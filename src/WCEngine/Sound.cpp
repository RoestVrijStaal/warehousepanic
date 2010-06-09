#include "Sound.h"

#if defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)
#include <SDL_mixer/SDL_mixer.h>
#else
#include <SDL/SDL_mixer.h>
#endif

namespace gdn
{
	Sound::Sound() : buffer( NULL ), channel( -1 )
	{
	}

	Sound::Sound( SoundBuffer& newbuffer ) : buffer( &newbuffer ), channel( -1 )
	{
	}

	Sound::~Sound()
	{
	}

	void Sound::Play()
	{
		if ( buffer and buffer->GetBuffer() )
			Mix_PlayChannel( -1, buffer->GetBuffer(), 0 );
	}
}
