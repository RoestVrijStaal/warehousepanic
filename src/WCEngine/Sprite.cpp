#include "Sprite.h"

namespace gdn
{
	Sprite::Sprite() : image( NULL )
	{
	}

	Sprite::Sprite( Image& newimage )
	{
		image = &newimage;
	}

	Sprite::~Sprite()
	{
	}

	void Sprite::SetImage( Image& newimage )
	{
		image = &newimage;
	}

	Image* Sprite::GetImage()
	{
		return image;
	}

	void Sprite::SetPosition( Vector2f newpos )
	{
		pos = newpos;
	}
	void Sprite::SetPosition( float newx, float newy )
	{
		pos.x = newx;
		pos.y = newy;
	}
	Vector2f& Sprite::GetPosition()
	{
		return pos;
	}
	void Sprite::SetCenter( float newx, float newy )
	{
		offset.x = newx;
		offset.y = newy;
	}
	Vector2f& Sprite::GetCenter()
	{
		return offset;
	}
}
