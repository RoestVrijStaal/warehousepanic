#ifndef CRATE_H
#define CRATE_H

#include "Conveyor.h"
#include "Object.h"
#include "Settings.h"
#include <set>



class Crate : public Object
{
public:
	Crate( float x, float y, int direction, GameColor::ColorType thecolor, unsigned int thevalue )
	{
		// Set type of this object (used in game)
		type = Object::CRATE;

		// Inherited from Object
		pos.x = x;
		pos.y = y;
		dir = direction;
		connected = NULL;
		color = thecolor;
		value = thevalue;

		SetSprite();
	}
	unsigned int value;
	std::set<int> visited; // map index of tiles visited (used for counting points)

protected:
private:
};

#endif // CRATE_H
