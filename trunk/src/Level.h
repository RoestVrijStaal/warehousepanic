#ifndef LEVEL_H
#define LEVEL_H

#include "Object.h"
#include "Conveyor.h"
#include "Gate.h"
#include "Truck.h"
#include "Settings.h"
#include "Functions.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>



class Level
{
public:
	Level()
	{
		width = height = /*levelTime =*/ curTime = 0;
		crateSpeed = crateInterval = crateSpeedIncrement = 0.0f;
		cratesPerTruck = 10;
		truckDelay = 5 * 100;   // Five seconds
		amountOfTrucks = 5;
	}

	Level( std::string filename )
	{
		curTime = 0;
		std::ifstream myfile (filename.c_str());
		if (myfile.is_open())
		{
			while (! myfile.eof() )
			{
				std::string line;
				getline(myfile, line);

				std::string key = line.substr(0, line.find("="));
				std::string value = line.substr(line.find("=") + 1);

				if ( key == "width" )
				{
					StringToInt(value, width);
				}
				else if ( key == "height" )
				{
					StringToInt(value, height);
				}
				/*else if ( key == "leveltime" )
				{
					StringToLong(value, levelTime);
				}*/
				else if ( key == "cratespeed" )
				{
					int tmp;
					StringToInt(value, tmp);
					crateSpeed = (float)tmp / 10000000.0f;
				}
				else if ( key == "crateinterval" )
				{
					int tmp;
					StringToInt(value, tmp);
					crateInterval = (float)tmp;
				}
				else if ( key == "cratespeedincrement" )
				{
					int tmp;
					StringToInt(value, tmp);
					crateSpeedIncrement = (float)tmp / 100000000.0f;
				}
				else if ( key == "cratespertruck" )
				{
				    StringToInt(value, cratesPerTruck);
				}
				else if ( key == "truckdelay" )
				{
				    StringToInt(value, truckDelay);
				}
				else if ( key == "amountoftrucks" )
				{
				    StringToInt(value, amountOfTrucks);
				}
				else if ( key == "tiles" )
				{
					objects = std::vector<Object*>( width * height, (Object*)NULL );

					// Process each tile
					std::set<GameColor::ColorType> colorSet;
					size_t idx = 0;
					while (idx < value.size())
					{
						switch(value[idx])
						{
							case 'A':
								// No tile
								break;
							case 'B':
								objects[idx] = new Conveyor(idx % 18, idx / 18, Dir::RIGHT);
								break;
							case 'C':
								objects[idx] = new Conveyor(idx % 18, idx / 18, Dir::UP);
								break;
							case 'D':
								objects[idx] = new Conveyor(idx % 18, idx / 18, Dir::LEFT);
								break;
							case 'E':
								objects[idx] = new Conveyor(idx % 18, idx / 18, Dir::DOWN);
								break;
							case 'F':
								objects[idx] = new Conveyor(idx % 18, idx / 18, Dir::RIGHT, true);
								break;
							case 'G':
								objects[idx] = new Conveyor(idx % 18, idx / 18, Dir::UP, true);
								break;
							case 'H':
								objects[idx] = new Conveyor(idx % 18, idx / 18, Dir::LEFT, true);
								break;
							case 'I':
								objects[idx] = new Conveyor(idx % 18, idx / 18, Dir::DOWN, true);
								break;
							case 'J':
								objects[idx] = new Gate(idx % 18, idx / 18, Dir::RIGHT, GameColor::BLUE);
								colorSet.insert( GameColor::BLUE );
								break;
							case 'K':
								objects[idx + width] = new Gate(idx % 18, idx / 18 + 1, Dir::UP, GameColor::BLUE); // +1 and +width because level editor handle is upper right corner, not entrance to gate
								colorSet.insert( GameColor::BLUE );
								break;
							case 'L':
								objects[idx] = new Gate(idx % 18, idx / 18, Dir::RIGHT, GameColor::GREEN);
								colorSet.insert( GameColor::GREEN );
								break;
							case 'M':
								objects[idx + width] = new Gate(idx % 18, idx / 18 + 1, Dir::UP, GameColor::GREEN);
								colorSet.insert( GameColor::GREEN );
								break;
							case 'N':
								objects[idx] = new Gate(idx % 18, idx / 18, Dir::RIGHT, GameColor::ORANGE);
								colorSet.insert( GameColor::ORANGE );
								break;
							case 'O':
								objects[idx + width] = new Gate(idx % 18, idx / 18 + 1, Dir::UP, GameColor::ORANGE);
								colorSet.insert( GameColor::ORANGE );
								break;
							case 'P':
								objects[idx] = new Gate(idx % 18, idx / 18, Dir::RIGHT, GameColor::PURPLE);
								colorSet.insert( GameColor::PURPLE );
								break;
							case 'Q':
								objects[idx + width] = new Gate(idx % 18, idx / 18 + 1, Dir::UP, GameColor::PURPLE);
								colorSet.insert( GameColor::PURPLE );
								break;
							case 'R':
								objects[idx] = new Gate(idx % 18, idx / 18, Dir::RIGHT, GameColor::RED);
								colorSet.insert( GameColor::RED );
								break;
							case 'S':
								objects[idx + width] = new Gate(idx % 18, idx / 18 + 1, Dir::UP, GameColor::RED);
								colorSet.insert( GameColor::RED );
								break;
							case 'T':
								objects[idx] = new Gate(idx % 18, idx / 18, Dir::RIGHT, GameColor::YELLOW);
								colorSet.insert( GameColor::YELLOW );
								break;
							case 'U':
								objects[idx + width] = new Gate(idx % 18, idx / 18 + 1, Dir::UP, GameColor::YELLOW);
								colorSet.insert( GameColor::YELLOW );
								break;
							// Trucks
							case 'V':
							case 'W':
								{
									Truck* t;
									if ( value[idx] == 'V' )
										// Again, shift it 1 to right because level editor handle is upper right of truck
										t = new Truck(idx % 18 + 1, idx / 18, Dir::RIGHT);
									else
										t = new Truck(idx % 18, idx / 18, Dir::UP);

									t->intervalmax = (int)crateInterval;
									t->interval = rand() % (int)crateInterval;
									t->delay = 0;
									t->delayrevert = 5 * 100;
									t->crates = t->craterevert = cratesPerTruck;
									t->active = false;
									t->soundPlaying = false;
									objects[idx] = t;
								}
								break;
							default:
								break;
						}
						++idx;
					}

					// Copy colors from set into color vector
					for ( std::set<GameColor::ColorType>::iterator it = colorSet.begin(); it != colorSet.end(); ++it )
					{
						colors.push_back( *it );
					}
				}
			}
			myfile.close();
		}
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

	int GetIndex( int x, int y )
	{
		return x + y * width;
	}

	Object* GetObjectAt( int x, int y )
	{
		int index = GetIndex( x, y );

		// Out side level then return NULL
		if ( x >= 0 and x < width and y >= 0 and y < height )
			return objects[index];
		else
		{
			return NULL;
		}
	}

	void Update()
	{
		crateSpeed += crateSpeedIncrement;
		++curTime;
	}

	/*bool GetTimeDone()
	{
		return levelTime < curTime;
	}*/

	float GetCrateSpeed()
	{
		return crateSpeed;
	}

	GameColor::ColorType GetRandomColor()
	{
		return colors[rand() % colors.size()];
	}

	int width;
	int height;
	float crateSpeed;
	float crateInterval;
	float crateSpeedIncrement;
	//long levelTime;
	int curTime;
	std::vector<Object*> objects;
	std::vector<GameColor::ColorType> colors;
	int cratesPerTruck;
	int truckDelay;
	int amountOfTrucks;
protected:
private:
};

#endif // LEVEL_H
