#ifndef TRUCK_H
#define TRUCK_H

#include "Object.h"
#include "Settings.h"


#include <vector>


class Truck : public Object
{
public:
	Truck( float x, float y, int direction )
	{
		// Set type of this object (used in game)
		type = Object::TRUCK;

		// Inheriited from Object
		targetpos.x = x;
		targetpos.y = y;
		dir = direction;
		connected = NULL;
		if ( dir == Dir::RIGHT )
		{
		    pos.x = targetpos.x - 5;
		    pos.y = targetpos.y;
		    cdir = 0.02;
		}
		else
		{
		    pos.x = targetpos.x;
		    pos.y = targetpos.y + 5;
		    cdir = -0.02;
		}
        active = false;
        crates = 10;
        craterevert = 10;
		SetSprite();
	}

	// Some more properties on a truck
	int intervalmax;
	int interval;
	int delay;
	bool active;
	std::vector<GameColor::ColorType> colors;
	gdn::Vector2f targetpos;    // This is for truck animation.
	float cdir;
	int crates;
	int craterevert;
	int delayrevert;

protected:
private:
};

#endif // TRUCK_H
