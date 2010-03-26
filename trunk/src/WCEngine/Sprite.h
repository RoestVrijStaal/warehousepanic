#ifndef SPRITE_H
#define SPRITE_H

#include "Vector2f.h"
#include "Image.h"

namespace gdn
{
	class Sprite
	{
		public:
			Sprite();
			Sprite( Image& newimage );
			virtual ~Sprite();

			void SetImage( Image& newimage );
			Image* GetImage();
			void SetPosition( Vector2f newpos );
			void SetPosition( float newx, float newy );
			Vector2f& GetPosition();
			void SetCenter( float newx, float newy );
			Vector2f& GetCenter();

		protected:
			Vector2f pos;
			Vector2f offset;
			Image* image;

		private:
	};
}

#endif // SPRITE_H
