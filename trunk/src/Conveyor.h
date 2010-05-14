#ifndef CONVEYOR_H
#define CONVEYOR_H

#include "Level.h"
#include "Object.h"
#include "Crate.h"

class Conveyor : public Object
{
public:
	Conveyor( float x, float y, int direction, bool isASwitch = false, bool isSwitchStartLeft = true )
	{
		// Set type of this object (used in game)
		type = Object::CONVEYOR;

		// Position is inherited from Object
		pos.x = x;
		pos.y = y;
		dir = direction;
		connected = NULL;

		isSwitch = isASwitch;
		isSwitchLeft = isSwitchStartLeft;

		SetSprite();
	}

	// Returns the direction this conveyor belt is currently leading. 0=right, 1=up, 2=left, 3=down. Like unit circle
	int GetCurDirection()
	{
		// If this is not a switch, then just return direction
		if ( !isSwitch )
			return dir;

		// Otherwise calculate if turn left or right
		else
			if ( isSwitchLeft )
				return ( dir + 1 ) % 4; // Modulus 4 makes result 0 if dir+1 is 4. That way it wraps around as directions go from 0-3
			else
				if ( ( dir - 1 ) == -1 ) // Wrap around the other way
					return 3;
				else
					return dir - 1;
	}

	void Switch()
	{
		isSwitchLeft = !isSwitchLeft;
	}

	bool isSwitch;
	bool isSwitchLeft;

protected:
private:
};

#endif // CONVEYOR_H
