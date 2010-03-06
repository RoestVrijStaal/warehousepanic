#ifndef CRATE_H
#define CRATE_H

#include "Conveyor.h"
#include "Object.h"
#include "Settings.h"



class Crate : public Object
{
public:
	Crate( float x, float y, int direction, GameColor::ColorType thecolor )
	{
		// Set type of this object (used in game)
		type = Object::CRATE;

		// Inherited from Object
		pos.x = x;
		pos.y = y;
		dir = direction;
		connected = NULL;
		color = thecolor;

		SetSprite();
	}

protected:
private:
};

#endif // CRATE_H
