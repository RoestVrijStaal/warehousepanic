#ifndef ANIMATION_H
#define ANIMATION_H

#include "Vector2f.h"
#include "Image.h"
#include "Sprite.h"
#include <vector>

namespace gdn
{
	class Animation : public Sprite
	{
		public:
			Animation();
			Animation( Image& firstFrame );
			virtual ~Animation();

			void Play();
			bool IsPlaying();
			void Pause();
			void Stop();
			void Step();

			void SetLoop( bool loop );
			void SetSpeed( float fps );

			void AddFrame( Image& newimage );
			Image* GetFrame( int idx = CURRENT_FRAME );
			void SetImage( Image& newimage ); // Sets current image

		protected:
			enum FRAME_IDX { CURRENT_FRAME = -1 };
			std::vector<Image*> frames;
			bool isLooping;
			bool isPlaying;
			float fps; // Frames per step
			float curFrame;

		private:
	};
}

#endif // ANIMATION_H
