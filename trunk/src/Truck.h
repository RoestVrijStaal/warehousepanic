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
		pos.x = x;
		pos.y = y;
		dir = direction;
		connected = NULL;

		SetSprite();
	}

	// Some more properties on a truck
	int intervalmax;
	int interval;
	int delay;
	bool active;
	std::vector<GameColor::ColorType> colors;

protected:
private:
};

#endif // TRUCK_H
