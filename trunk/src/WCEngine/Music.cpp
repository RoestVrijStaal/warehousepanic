#include "Music.h"


namespace gdn
{
	Music* Music::currentlyPlaying = NULL;

	Music::Music() : buffer( NULL ), isLoop( false )
	{
	}

	Music::~Music()
	{
		if ( buffer )
			Mix_FreeMusic( buffer );
	}

	bool Music::LoadFromFile( std::string filename )
	{
		if ( buffer )
			Mix_FreeMusic( buffer );

		buffer = Mix_LoadMUS( filename.c_str() );
		return buffer != NULL;
	}

	void Music::SetLoop( bool on )
	{
		isLoop = on;
	}

	bool Music::IsPlaying()
	{
		return Music::currentlyPlaying == this;
	}

	void Music::Play()
	{
		if ( !buffer )
			return;

		Mix_FadeInMusic( buffer, (isLoop ? -1 : 1), 100 );
		Music::currentlyPlaying = this;
	}

	void Music::Stop()
	{
		if ( Music::currentlyPlaying == this )
			Mix_FadeOutMusic( 100 );
	}
}
