#include "SceneGame.h"

#include "WCEngine/EventManager.h"
#include "WCEngine/ResourceManager.h"

#include <iostream>
using namespace std;



// This is the important part. You need to give this scene a name. I call this one game
SceneGame::SceneGame() : Scene( "game" )
{
	App.AddScene( this );
}

SceneGame::~SceneGame()
{
}

void SceneGame::Initialize()
{
	level = Level( "" ); // TODO: How do we choose level?
	for ( std::vector<Object*>::iterator it = level.objects.begin(); it != level.objects.end(); ++it )
	{
		if ( *it != NULL )
		{
			objects.push_back( *it );

			// If it is a gate, add the gate's background and conveyor belt
			if ( (**it).type == Object::GATE )
			{
				Object& obj = *(Gate*)(*it);
				toDelete.push_back( new Gate( obj.pos.x, obj.pos.y, obj.dir, obj.color, true ) ); // The background of the gate
				objects.push_back( toDelete.back() );
				toDelete.push_back( new Conveyor( obj.pos.x, obj.pos.y, obj.dir ) );
				objects.push_back( toDelete.back() );
			}
		}
	}

	//--------------------------
	//pbutton1 = sf::Shape::Rectangle(40,100,280,150,sf::Color(0,100,250),2.f,sf::Color(0,0,0));
	//pbutton2 = sf::Shape::Rectangle(40,170,280,220,sf::Color(0,100,250),2.f,sf::Color(0,0,0));

	//Other stuff
	isMouseDown = false;
	isPaused = false;
	points = 0;
	csel = 0;
}

void SceneGame::Terminate()
{
	// Free any resources reserved in initialize()
	for ( std::list<Object*>::iterator it = toDelete.begin(); it != toDelete.end(); it++ )
		delete *it;
	toDelete.clear();
	objects.clear(); // Level clears its own objects
	level.Terminate();
}

void SceneGame::Step()
{
	//Events
	sf::Vector2f mousepos(window->GetInput().GetMouseX(),window->GetInput().GetMouseY());
	bool newMouseButton = window->GetInput().IsMouseButtonDown( sf::Mouse::Left );

	if (mousepos.x > pbutton1.GetPointPosition(0).x and mousepos.y > pbutton1.GetPointPosition(0).y and
		mousepos.x < pbutton1.GetPointPosition(2).x and mousepos.y < pbutton1.GetPointPosition(2).y and
		isPaused == true)
	{
		csel = 1;
	}
	else if (mousepos.x > pbutton2.GetPointPosition(0).x and mousepos.y > pbutton2.GetPointPosition(0).y and
		mousepos.x < pbutton2.GetPointPosition(2).x and mousepos.y < pbutton2.GetPointPosition(2).y and
		isPaused == true)
	{
		csel = 2;
	}
	else
	{
		csel = 0;
	}

	// Handle mouse-down event
	if (newMouseButton and isMouseDown == false)
	{
		if (isPaused == false)
		{
			// Translate screen coordinates to level grid coordinates
			sf::Vector2f screenPos = TransformScreenToMap( mousepos );

			Object* obj = level.GetObjectAt( (int)screenPos.x, (int)screenPos.y );
			if ( obj )
			{
				switch ( obj->type )
				{
					case Object::CONVEYOR:
						{
							Conveyor& c = *(Conveyor*)obj;
							c.Switch();
						}
						break;

					// Do nothing for the rest of the objects
					default:
						break;
				}
			}
		}

		// Handle mouse-down event game paused
		else
		{
			if (csel == 1)
			{
				isPaused = false;
			}
			else if (csel == 2)
			{
				EventMgr.PushEvent( ENGINE, GameEvent::ChangeSceneEvent( "menu" ) );
			}
		}
	}

	// Pause on space
	if (window->GetInput().IsKeyDown(sf::Key::Space) and isPaused == false)
	{
		if (isPaused == false)
		{
			isPaused = true;
			csel = 0;
		}
	}

	//Compute
	if (isPaused == false)
	{
		// Update game
		for (std::list<Object*>::iterator it = objects.begin(); it != objects.end(); ++it )
		{
			switch ( (**it).type )
			{
				case Object::CRATE:
					// DoCrate returns true when crate should be deleted
					if ( DoCrate( *(Crate*)(*it) ) )
					{
						delete *it; // Free memory
						objects.erase( it ); // Remove pointer from vector
						--it; // Go back one step, so we don't skip object after this. See erase() for more detail
					}
					break;

				case Object::TRUCK:
					if ( DoTruck( *(Truck*)(*it) ) )
					{
						delete *it;
						objects.erase( it );
						--it;
					}
					break;

				// Ignore other objects
				default:
					break;
			}

			// Sort object for drawing!
			std::list<Object*>::iterator tmp1 = it; // Temporary iterator to swap this gameobject backward (if it changed position)
			std::list<Object*>::iterator tmp2 = it;
			--tmp1;

			// Loop until we reach past beginning of list
			do
			{
				// We are done
				if ( tmp2 == objects.begin() )
					break;

				// Consider height into equation
				float height1 = ObjectHeight[ (**tmp1).type ];
				float height2 = ObjectHeight[ (**tmp2).type ];
				if ( GetDistanceSQ( (**tmp2).pos, SORT_POINT ) + height2 * height2 < GetDistanceSQ( (**tmp1).pos, SORT_POINT ) + height1 * height1 )
				{
					// Swap
					Object* tmpObject = *tmp1;
					*tmp1 = *tmp2;
					*tmp2 = tmpObject;
					--tmp1;
					--tmp2;
				}

				// Didn't need to swap, so we are done
				else
				{
					break;
				}
			} while ( true );
		} // Loop through game objects
	} // Game not poused

	isMouseDown = newMouseButton;
}

void SceneGame::Draw()
{
	//sf::Sprite bg( ResMgr.GetImage( "level background" ) );
	//bg.SetColor( sf::Color( 60, 60, 60 ) );
	//window->Draw( bg );
	window->Clear( sf::Color(100,100,100) );

	if (isPaused == true)
	{
		window->Draw(str_paused_msg1);
		if (csel == 1)
		{
			pbutton1 = sf::Shape::Rectangle(40,100,280,150,sf::Color(0,100,250),3.f,sf::Color(255,210,0));
			pbutton2 = sf::Shape::Rectangle(40,170,280,220,sf::Color(0,100,250),2.f,sf::Color(0,0,0));
		}
		else if (csel == 2)
		{
			pbutton1 = sf::Shape::Rectangle(40,100,280,150,sf::Color(0,100,250),2.f,sf::Color(0,0,0));
			pbutton2 = sf::Shape::Rectangle(40,170,280,220,sf::Color(0,100,250),3.f,sf::Color(255,210,0));
		}
		else
		{
			pbutton1 = sf::Shape::Rectangle(40,100,280,150,sf::Color(0,100,250),2.f,sf::Color(0,0,0));
			pbutton2 = sf::Shape::Rectangle(40,170,280,220,sf::Color(0,100,250),2.f,sf::Color(0,0,0));
		}
		window->Draw(pbutton1);
		window->Draw(pbutton2);
		window->Draw(str_paused_msg2);
		window->Draw(str_paused_msg3);
	}
	else
	{
		// Draw all objects
		for ( std::list<Object*>::iterator it = objects.begin(); it != objects.end(); ++it )
		{
			Object& obj = (**it);
			sf::Vector2f screenPos = TransformMapToScreen( obj.pos );
			switch ( obj.type )
			{
				case Object::CRATE:
					obj.sprite.SetPosition( screenPos.x, screenPos.y - 5 ); // Draw atop conveyor
					break;

				// Conveyors are special. They need to draw the correct branching sprite
				case Object::CONVEYOR:
					if ( ((Conveyor&)obj).isSwitch )
					{
						std::stringstream name;
						name << "conveyor " << obj.dir;
						if ( ((Conveyor&)obj).isSwitchLeft )
							name << " turn left";
						else
							name << " turn right";
						obj.sprite.SetImage( ResMgr.GetImage( name.str() ) );
					}
					// No break, fall through to set the position of conveyor too

				case Object::GATE:
				case Object::GATE_BACKGROUND:
				case Object::INCINERATOR:
				case Object::TRUCK:
				default:
					obj.sprite.SetPosition( screenPos );
					break;
			}
			window->Draw( obj.sprite );
		} // End loop through all objects

		stringstream score;
		score << "Score: " << points;
		str_score.SetText(score.str());
		str_score.SetPosition( 10, 200 );
		window->Draw(str_score);
	} // Game not paused
}



// Helper functions
sf::Vector2f SceneGame::TransformScreenToMap( sf::Vector2f& pos )
{
	static float cosval = cos( -M_PI / 4.0 );
	static float sinval = sin( -M_PI / 4.0 );

	// Translate to center of screen
	sf::Vector2f descreen(
		pos.x - 160,
		pos.y - 120 );

	// Scale to fit screen resolution
	sf::Vector2f descaled(
		descreen.x / 28.4f,
		descreen.y / 28.4f );

	// scale up y axis
	descaled.y *= 2.0f;

	// Rotate 45 degrees
	sf::Vector2f derotated(
		descaled.x * cosval + descaled.y * sinval,
		descaled.y * cosval - descaled.x * sinval );

	sf::Vector2f decentered(
		derotated.x + 0.5f + (float)level.width / 2.0f,
		derotated.y + 0.5f + (float)level.height / 2.0f );

	return decentered;
}

sf::Vector2f SceneGame::TransformMapToScreen( sf::Vector2f& pos )
{
	static float cosval = cos( M_PI / 4.0 );
	static float sinval = sin( M_PI / 4.0 );

	sf::Vector2f centered(
		pos.x - (float)level.width / 2.0f,
		pos.y - (float)level.height / 2.0f );

	// Rotate 45 degrees
	sf::Vector2f rotated(
		centered.x * cosval + centered.y * sinval,
		centered.y * cosval - centered.x * sinval );

	// scale down y axis
	rotated.y /= 2.0f;

	// Scale to fit screen resolution
	sf::Vector2f scaled(
		rotated.x * 28.4f,
		rotated.y * 28.4f );
		//rotated.x * 28.4864f,
		//rotated.y * 28.55f );

	// Translate to center of screen
	sf::Vector2f screen(
		scaled.x + 160,
		scaled.y + 120 );
	return screen;
}

float SceneGame::GetDistanceSQ( sf::Vector2f pos1, sf::Vector2f pos2 )
{
	sf::Vector2f diff( pos1.x - pos2.x, pos1.y - pos2.y );
	return diff.x * diff.x + diff.y * diff.y;
}

// Return true if crate done and should be deleted
bool SceneGame::DoCrate( Crate& crate )
{
	// If crate.dest is ever NULL, then the level is fucked up so just delete crate
	if ( crate.connected == NULL )
		return true;

	// If distance to destination less then movement this step, then
	// step to that square and then start toward next destination. This
	// becomes very nice to calculate since simulation is in normal
	// top-down view.
	float distLeft = level.GetCrateSpeed();

	while ( distLeft > 0.0f )
	{
		// We finally reached the center of this conveyor and are ready for next target
		if ( GetDistanceSQ( crate.pos, crate.connected->pos ) <= distLeft * distLeft )
		{
			float curDist = sqrtf( GetDistanceSQ( crate.pos, crate.connected->pos ) );
			crate.pos = crate.connected->pos; // Snap to center

			// Go in direction this conveyor (or gate) says
			switch ( crate.connected->type )
			{
				case Object::CONVEYOR:
					crate.dir = ((Conveyor*)crate.connected)->GetCurDirection();
					break;

				// We landed on gate, so break link between gate and crate
				case Object::GATE:
					if ( crate.color == crate.connected->color )
					{
						++points;
					}
					else
					{
						--points;
					}
					crate.connected->connected = NULL; // "Gate, I am not on you anymore"
					crate.connected = NULL;
					return true; // Delete crate
					break;

				default:
					crate.dir = crate.connected->dir;
					break;
			}

			// Find next destination
			Object* nextDest = NULL;
			if ( crate.dir == Dir::RIGHT )
				nextDest = level.GetObjectAt( (int)crate.pos.x + 1, (int)crate.pos.y );
			else if ( crate.dir == Dir::UP )
				nextDest = level.GetObjectAt( (int)crate.pos.x, (int)crate.pos.y - 1 );
			else if ( crate.dir == Dir::LEFT )
				nextDest = level.GetObjectAt( (int)crate.pos.x - 1, (int)crate.pos.y );
			else if ( crate.dir == Dir::DOWN )
				nextDest = level.GetObjectAt( (int)crate.pos.x, (int)crate.pos.y + 1 );

			// Is there no conveyor at the end of this one, then just delete crate, level is fubar
			if ( nextDest == NULL )
				return true;

			// Only go to next if next one is free
			if ( nextDest->connected == NULL )
			{
				crate.connected->connected = NULL; // Release conveyor we are standing on
				nextDest->connected = &crate; // Take the next one
				crate.connected = nextDest;
				distLeft -= curDist;
			}

			// Else next square occupied, so stop moving
			else
			{
				distLeft = 0.0f;
			}
		}

		// Will not reach center of conveyor, so move closer
		else
		{
			sf::Vector2f diff( crate.connected->pos.x - crate.pos.x, crate.connected->pos.y - crate.pos.y );
			float length = sqrtf( diff.x * diff.x + diff.y * diff.y );
			diff.x /= length;
			diff.y /= length;

			crate.pos.x += diff.x * distLeft;
			crate.pos.y += diff.y * distLeft;
			distLeft = 0.0f;
		}
	}

	return false;
}

bool SceneGame::DoTruck( Truck& truck )
{
	if ( truck.active )
	{
		if ( truck.interval <= 0 )
		{
			truck.interval = truck.intervalmax;

			// Get random color
			objects.push_back( new Crate( truck.pos.x, truck.pos.y, truck.dir, truck.colors[rand() % truck.colors.size()] ) );
			Crate& crate = *((Crate*)objects.back());

			// Assign first destination to get crate moving
			if ( truck.dir == Dir::RIGHT )
				crate.connected = level.GetObjectAt( (int)truck.pos.x + 1, (int)truck.pos.y );
			else if ( truck.dir == Dir::UP )
				crate.connected = level.GetObjectAt( (int)truck.pos.x, (int)truck.pos.y - 1 );
			else if ( truck.dir == Dir::LEFT )
				crate.connected = level.GetObjectAt( (int)truck.pos.x - 1, (int)truck.pos.y );
			else if ( truck.dir == Dir::DOWN )
				crate.connected = level.GetObjectAt( (int)truck.pos.x, (int)truck.pos.y + 1 );
		}
		else if ( truck.delay <= 0 )
		{
			truck.interval -= 1;
		}
		else
		{
			truck.delay -= 1;
		}
	}

	// TODO: implement truck done and driving away method
	return false;
}



// This makes sure the scene is added to the engine!
SceneGame* game = new SceneGame();
