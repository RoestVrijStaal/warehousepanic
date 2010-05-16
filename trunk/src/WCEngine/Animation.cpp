#include "Animation.h"
#include "Application.h"

namespace gdn
{
	Animation::Animation() : Sprite()
	{
		isLooping = false;
		isPlaying = false;
		fps = 1.0f;
		curFrame = 0.0f;
		App.AddAnimation( this );
	}

	Animation::Animation( Image& newimage ) : Sprite( newimage )
	{
		isLooping = false;
		isPlaying = false;
		fps = 1.0f;
		curFrame = 0.0f;
		frames.push_back( &newimage );
		App.AddAnimation( this );
	}

	Animation::~Animation()
	{
		App.RemoveAnimation( this );
	}

	void Animation::SetImage( Image& newimage )
	{
		frames[curFrame] = &newimage;
		Sprite::SetImage( newimage );
	}

	void Animation::Play()
	{
		isPlaying = true;

		// Restart if animation was done
		if ( curFrame >= (float)frames.size() )
		{
			curFrame = 0.0f;
		}
	}

	bool Animation::IsPlaying()
	{
		return isPlaying;
	}

	void Animation::Pause()
	{
		isPlaying = false;
	}

	void Animation::Stop()
	{
		isPlaying = false;
		curFrame = 0.0f;
	}

	void Animation::Step()
	{
		if ( isPlaying && frames.size() > 0 )
		{
			curFrame += fps;

			// Wrap around if looping
			while ( isLooping && curFrame >= (float)frames.size() )
			{
				curFrame -= (float)frames.size();
			}

			// Done?
			if ( curFrame >= (float)frames.size() )
			{
				isPlaying = false;
			}
			else
			{
				image = frames[(int)curFrame];
			}
		}
	}

	void Animation::SetLoop( bool loop )
	{
		isLooping = loop;
	}

	void Animation::SetSpeed( float fps )
	{
		this->fps = fps;
	}

	void Animation::AddFrame( Image& newimage )
	{
		frames.push_back( &newimage );

		// First frame then use it
		if ( frames.size() == 1 )
		{
			image = &newimage;
		}
	}
}
