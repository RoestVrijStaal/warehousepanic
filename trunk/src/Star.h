#ifndef STAR_H
#define STAR_H

#include "WCEngine/GDN.h"

class Star
{
public:
	Star( gdn::Image& img, float xCenter, float yCenter, bool toRemove = true )
	{
		sprite.SetImage( img );
		sprite.SetCenter( xCenter, yCenter );
		willRemove = toRemove;
	}

	// Position on screen.
	gdn::Vector2f pos;
	gdn::Vector2f target;
	gdn::Vector2f vel;

	// Delay before animation starts
	int delay;

	bool willRemove;

	// Sprite to draw. Stored here so offset (center) can be set only once
	gdn::Sprite sprite;

protected:
private:
};

#endif // STAR_H
