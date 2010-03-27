#include "Sound.h"

#include <SDL/SDL_mixer.h>

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
