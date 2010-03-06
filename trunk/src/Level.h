#ifndef LEVEL_H
#define LEVEL_H

#include "Object.h"
#include "Conveyor.h"
#include "Gate.h"
#include "Truck.h"
#include "Settings.h"

#include <string>
#include <vector>



class Level
{
public:
	Level()
	{
		width = height = levelTime = 0;
	}

	Level( std::string filename )
	{
		// TODO: Load from file
		levelTime = 0;
		crateSpeed = 0.01f; // Squares every step
		width = 18;
		height = 18;
		objects = std::vector<Object*>( width * height, (Object*)NULL );

		// Colors
		colors.push_back( GameColor::YELLOW );
		colors.push_back( GameColor::BLUE );
		colors.push_back( GameColor::RED );
		colors.push_back( GameColor::ORANGE );

		// Add some conveyor belts
		Truck* t = new Truck( 7, 17, Dir::UP );
		t->intervalmax = 350;
		t->interval = 10;
		t->delay = 0;
		t->active = true;
		t->colors = colors;

		objects[  7 + 17 * width] = t;
		objects[  7 + 16 * width] = new Conveyor(  7, 16, Dir::UP );
		objects[  7 + 15 * width] = new Conveyor(  7, 15, Dir::UP );
		objects[  7 + 14 * width] = new Conveyor(  7, 14, Dir::UP );
		objects[  7 + 13 * width] = new Conveyor(  7, 13, Dir::UP );
		objects[  7 + 12 * width] = new Conveyor(  7, 12, Dir::UP );
		objects[  7 + 11 * width] = new Conveyor(  7, 11, Dir::UP );
		objects[  7 + 10 * width] = new Conveyor(  7, 10, Dir::UP, true );
			objects[  8 + 10 * width] = new Conveyor(  8, 10, Dir::RIGHT );
			objects[  9 + 10 * width] = new Conveyor(  9, 10, Dir::RIGHT );
			objects[ 10 + 10 * width] = new Conveyor( 10, 10, Dir::RIGHT, true );
				objects[ 10 + 11 * width] = new Conveyor( 10, 11, Dir::DOWN );
				objects[ 10 + 12 * width] = new Conveyor( 10, 12, Dir::DOWN );
				objects[ 10 + 13 * width] = new Conveyor( 10, 13, Dir::RIGHT );
				objects[ 11 + 13 * width] = new Conveyor( 11, 13, Dir::RIGHT );
				objects[ 12 + 13 * width] = new     Gate( 12, 13, Dir::RIGHT, GameColor::GREEN );
			objects[ 10 +  9 * width] = new Conveyor( 10,  9, Dir::UP );
		objects[  6 + 10 * width] = new Conveyor(  6, 10, Dir::LEFT );
		objects[  5 + 10 * width] = new Conveyor(  5, 10, Dir::UP );
		objects[  5 +  9 * width] = new Conveyor(  5,  9, Dir::UP );
		objects[  5 +  8 * width] = new Conveyor(  5,  8, Dir::UP, true );
			objects[  4 +  8 * width] = new Conveyor(  4,  8, Dir::UP );
			objects[  4 +  7 * width] = new     Gate(  4,  7, Dir::UP, GameColor::YELLOW );
		objects[  6 +  8 * width] = new Conveyor(  6,  8, Dir::RIGHT );
		objects[  7 +  8 * width] = new Conveyor(  7,  8, Dir::RIGHT );
		objects[  8 +  8 * width] = new Conveyor(  8,  8, Dir::RIGHT );
		objects[  9 +  8 * width] = new Conveyor(  9,  8, Dir::RIGHT );
		objects[ 10 +  8 * width] = new Conveyor( 10,  8, Dir::RIGHT );
		objects[ 11 +  8 * width] = new Conveyor( 11,  8, Dir::RIGHT );
		objects[ 12 +  8 * width] = new Conveyor( 12,  8, Dir::RIGHT );
		objects[ 13 +  8 * width] = new Conveyor( 13,  8, Dir::RIGHT, true );
			objects[ 13 +  7 * width] = new Conveyor( 13,  7, Dir::UP );
			objects[ 13 +  6 * width] = new Conveyor( 13,  6, Dir::UP );
			objects[ 13 +  5 * width] = new Conveyor( 13,  5, Dir::UP );
			objects[ 13 +  4 * width] = new Conveyor( 13,  4, Dir::UP, true );
				objects[ 14 +  4 * width] = new     Gate( 14,  4, Dir::RIGHT, GameColor::BLUE );
			objects[ 12 +  4 * width] = new Conveyor( 12,  4, Dir::LEFT );
			objects[ 11 +  4 * width] = new Conveyor( 11,  4, Dir::LEFT );
			objects[ 10 +  4 * width] = new Conveyor( 10,  4, Dir::LEFT );
			objects[  9 +  4 * width] = new Conveyor(  9,  4, Dir::LEFT, true );
				objects[  9 +  3 * width] = new     Gate(  9,  3, Dir::UP, GameColor::ORANGE );
			objects[  9 +  5 * width] = new Conveyor(  9,  5, Dir::DOWN );
			objects[  9 +  6 * width] = new Conveyor(  9,  6, Dir::DOWN );
			objects[  9 +  7 * width] = new Conveyor(  9,  7, Dir::DOWN );
			// Ends into another track
		objects[ 13 +  9 * width] = new Conveyor( 13,  9, Dir::DOWN );
		objects[ 13 + 10 * width] = new Conveyor( 13, 10, Dir::RIGHT );
		objects[ 14 + 10 * width] = new     Gate( 14, 10, Dir::RIGHT, GameColor::RED );


/*		for (int x = 0; x < 12; ++x )
			objects[ x + (11-x) * width] = new Conveyor( x, (11-x), Dir::UP );
		for (int x = 0; x < 12; ++x )
			objects[ (7+x) + (18-x) * width] = new Conveyor( (7+x), (18-x), Dir::UP );
		for (int x = 1; x < 7; ++x )
			objects[ (x) + (11+x) * width] = new Conveyor( (x), (11+x), Dir::UP );
		for (int x = 1; x < 7; ++x )
			objects[ (11+x) + (x) * width] = new Conveyor( (11+x), (x), Dir::UP );
*/

	}

	void Terminate()
	{
		for ( std::vector<Object*>::iterator it = objects.begin(); it != objects.end(); ++it )
		{
			if ( *it != NULL )
				delete *it;
		}
		objects.clear();
	}

	Object* GetObjectAt( int x, int y )
	{
		int index = x + y * width;

		// Out side level then return NULL
		if ( x >= 0 and x < width and y >= 0 and y < height )
			return objects[index];
		else
			return NULL;
	}

	void Update()
	{
		crateSpeed += 0.0001f; // These things should come from loading
		++levelTime;
	}

	float GetCrateSpeed()
	{
		return crateSpeed;
	}

	int width;
	int height;
	float crateSpeed;
	int levelTime;
	std::vector<Object*> objects;
	std::vector<GameColor::ColorType> colors;
protected:
private:
};

#endif // LEVEL_H
