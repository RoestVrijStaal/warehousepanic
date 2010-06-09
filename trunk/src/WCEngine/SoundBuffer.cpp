#include "SoundBuffer.h"

#if defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)
#include <SDL_mixer/SDL_mixer.h>
#else
#include <SDL/SDL_mixer.h>
#endif

namespace gdn
{
	SoundBuffer::SoundBuffer() : buffer( NULL )
	{
	}

	SoundBuffer::~SoundBuffer()
	{
		if ( buffer )
			Mix_FreeChunk( buffer );
	}

	bool SoundBuffer::LoadFromFile( std::string filename )
	{
		if ( buffer )
			Mix_FreeChunk( buffer );

		buffer = Mix_LoadWAV( filename.c_str() );
		return buffer != NULL;
	}

	Mix_Chunk* SoundBuffer::GetBuffer()
	{
		return buffer;
	}
}
