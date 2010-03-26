#ifndef OBJECT_H
#define OBJECT_H

#include "WCEngine/GDN.h"
#include "Settings.h"
#include <sstream>



// Height of objects (ordered by type enum in Object
const float ObjectHeight[] = { 0.0f, 6.0f, 6.8f, 0.0f, 0.0f, 30.0f }; // Height of the objects above (in map units (which is doh!!)



class Object
{
public:
	Object() {}

	enum ObjectType { CONVEYOR, CRATE, GATE, GATE_BACKGROUND, INCINERATOR, TRUCK, count }; // count not used

	// Type of object. So we can choose how to treat them in the gameloop
	ObjectType type;

	// Position on 2D level. Not graphical position
	gdn::Vector2f pos;

	// Facing direction, i.e. the direction of flow. 0=right, 1=up, 2=left, 3=down (see the unit circle for more info)
	int dir;

	// Some of the objects have a specific color
	GameColor::ColorType color;

	// Pointer to what this object is connected to. On crates it tells
	// where to go, on conveyor and gates it tells if it is occupied or
	// not.
	Object* connected;

	// Sprite to draw. Stored here so offcet (center) can be set only once
	gdn::Sprite sprite;

	void SetSprite()
	{
		std::stringstream name;

		// Name
		switch ( type )
		{
			case CONVEYOR:       name << "conveyor";    break;
			case CRATE:          name << "crate";       break;
			case GATE:           name << "gate";        break;
			case GATE_BACKGROUND:name << "gate bg";     break;
			case INCINERATOR:    name << "incinerator"; break;
			case TRUCK:          name << "truck";       break;
			default: break;
		}

		// Direction
		switch ( type )
		{
			case CONVEYOR:
				if ( dir == Dir::RIGHT or dir == Dir::LEFT )
					name << " 02";
				else
					name << " 13";
				break;
			case GATE:
			case GATE_BACKGROUND:
			case INCINERATOR:
			case TRUCK:
				name << " " << dir;
				break;
			default: break;
		}

		// Color
		switch ( type )
		{
			case CRATE:
			case GATE:
			case GATE_BACKGROUND:
				name << " " << GameColor::name[color];
				break;
			default: break;
		}
		sprite.SetImage( ResMgr.GetImage( name.str() ) );



		// Set center of sprite
		float x = 0.0f;
		float y = 0.0f;

		// Do the x offset
		if ( dir == Dir::RIGHT or dir == Dir::DOWN )
			x = 20;
		else
			x = sprite.GetImage()->GetWidth() - 20;

		// Do the y offset
		y = sprite.GetImage()->GetHeight() - 10;

		sprite.SetCenter(	x, y );

		// Right facing truck cannot be determined so we hardcode its offset here as being 2 squares long
		if ( type == TRUCK and dir == Dir::RIGHT )
		{
			sprite.SetCenter( x + 20, y - 10 );
		}
	}
protected:
private:
};

#endif // OBJECT_H
