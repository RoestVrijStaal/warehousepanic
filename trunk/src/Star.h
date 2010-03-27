#ifndef STAR_H
#define STAR_H

#include "WCEngine/GDN.h"

class Star
{
public:
	Star()
	{
		sprite.SetImage( ResMgr.GetImage( "star" ) );

		// Center handle
		float x = sprite.GetImage()->GetWidth() / 2;
		float y = sprite.GetImage()->GetHeight() / 2;
		sprite.SetCenter( x, y );
	}

	// Position on screen.
	gdn::Vector2f pos;
	gdn::Vector2f vel;

	// Delay before animation starts
	int delay;

	// Sprite to draw. Stored here so offset (center) can be set only once
	gdn::Sprite sprite;

protected:
private:
};

#endif // STAR_H
