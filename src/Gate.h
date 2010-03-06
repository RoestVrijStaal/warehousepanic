#ifndef GATE_H
#define GATE_H

#include "Object.h"
#include "Settings.h"



class Gate : public Object
{
public:

	// The isBackground is used with a lower height so that it will be drawn first (behind the box entering the gate)
	Gate( float x, float y, int direction, GameColor::ColorType thecolor, bool isBackground = false )
	{
		// Set type of this object (used in game)
		if ( isBackground )
			type = Object::GATE_BACKGROUND;
		else
			type = Object::GATE;

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

#endif // GATE_H
