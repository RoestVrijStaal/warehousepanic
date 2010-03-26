#ifndef STAR_H
#define STAR_H

#include "WCEngine/GDN.h"
#include "Settings.h"

class Star
{
public:
	Star() {}

	// Position on screen.
	gdn::Vector2f pos;

	// Sprite to draw. Stored here so offset (center) can be set only once
	gdn::Sprite sprite;

	void SetSprite()
	{
		sprite.SetImage( ResMgr.GetImage( "star" ) );

		// Set center of sprite
		float x = 0.0f;
		float y = 0.0f;

		// Do the x offset
        x = sprite.GetImage()->GetWidth() / 2;

		// Do the y offset
		y = sprite.GetImage()->GetHeight() / 2;

		sprite.SetCenter( x, y );
	}
protected:
private:
};

#endif // STAR_H
