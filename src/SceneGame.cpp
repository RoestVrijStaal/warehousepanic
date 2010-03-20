#include "SceneGame.h"

#include "WCEngine/EventManager.h"
#include "WCEngine/ResourceManager.h"
#include "WCEngine/Application.h"

#include <iostream>
using namespace std;



// This is the important part. You need to give this scene a name. I call this one game
SceneGame::SceneGame() : Scene( "game" )
{
}

SceneGame::~SceneGame()
{
}

void SceneGame::Initialize()
{
	// Level stuff
	level = Level( "levels/test level.lvl" ); // TODO: How do we choose level?
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

			// We keep a list of clickable objects also. Faster to search through when player clicks screen
			else if ( (**it).type == Object::CONVEYOR )
			{
				clickables.push_back( *it );
			}
		}
	}

	// Buttons
	pbuttonPause = sf::Sprite( ResMgr.GetImage( "button pause" ) );
	pbuttonPause.SetCenter( pbuttonPause.GetImage()->GetWidth() / 2.0f, pbuttonPause.GetImage()->GetHeight() / 2.0f );
	pbuttonPause.SetPosition(
		App.GetWidth() - pbuttonPause.GetImage()->GetWidth() / 2.0f - 5,
		pbuttonPause.GetImage()->GetWidth() / 2.0f + 5 ); // Top right corner
	pbuttonQuit = sf::Sprite( ResMgr.GetImage( "button quit" ) );
	pbuttonQuit.SetCenter( pbuttonQuit.GetImage()->GetWidth() / 2.0f, pbuttonQuit.GetImage()->GetHeight() / 2.0f );
	pbuttonQuit.SetPosition(
		App.GetWidth() - pbuttonPause.GetImage()->GetWidth() - pbuttonQuit.GetImage()->GetWidth() / 2.0f - 10,
		pbuttonQuit.GetImage()->GetHeight() / 2.0f + 5 ); // Top right corner next to pause button
	// We assign a new sprite to popup when we have some popup to display
	popup = NULL;

	// Sounds
	sndSwitch = sf::Sound( ResMgr.GetSound( "switch" ) );
	sndClick = sf::Sound( ResMgr.GetSound( "click" ) );

	//Other stuff
	isMouseDown = false;
	isPaused = false;
	isGameOver = false;
	timer = 0;
	points = 0;
}

void SceneGame::Terminate()
{
	// Free any resources reserved in initialize()
	for ( std::list<Object*>::iterator it = toDelete.begin(); it != toDelete.end(); it++ )
		delete *it;
	toDelete.clear();
	objects.clear(); // Level clears its own objects
	clickables.clear();
	level.Terminate();

	if ( popup )
	{
		delete popup;
		popup = NULL;
	}
}

void SceneGame::Step()
{
	//Events
	sf::Vector2f mousepos( App.GetWindow().GetInput().GetMouseX(), App.GetWindow().GetInput().GetMouseY()) ;
	bool newMouseButton = App.GetWindow().GetInput().IsMouseButtonDown( sf::Mouse::Left );

	// Handle mouse-down event
	if (newMouseButton and isMouseDown == false)
	{
		// If squared distance to button center is < then size of button squared, then we clicked inside it
		if ( GetDistanceSQ(mousepos, pbuttonPause.GetPosition()) < pbuttonPause.GetImage()->GetWidth() / 2.0f * pbuttonPause.GetImage()->GetWidth() / 2.0f )
		{
			sndClick.Play();
			isPaused = !isPaused;
			if ( isPaused )
			{
				pbuttonPause.SetImage( ResMgr.GetImage( "button pause active" ) );

				if ( popup )
					delete popup;
				popup = new sf::Sprite( ResMgr.GetImage( "text paused" ) );
				popup->SetCenter( popup->GetImage()->GetWidth() / 2.0f, popup->GetImage()->GetHeight() / 2.0f );
				popup->SetPosition( (float)App.GetWidth() / 2.0f, -(float)(popup->GetImage()->GetHeight()) / 2.0f ); // At top of screen (to animate falling down)
			}
			else
			{
				pbuttonPause.SetImage( ResMgr.GetImage( "button pause" ) );

				delete popup;
				popup = NULL;
			}
		}

		// Handle mouse-down event game paused
		if (isPaused)
		{
			// Clicked inside quit button?
			if ( GetDistanceSQ(mousepos, pbuttonQuit.GetPosition()) < pbuttonQuit.GetImage()->GetWidth() / 2.0f * pbuttonQuit.GetImage()->GetWidth() / 2.0f )
			{
				sndClick.Play();
				isGameOver = true;
				timer = 50;
				pbuttonQuit.SetImage( ResMgr.GetImage( "button quit active" ) );
			}

		}

		// Mouse down event, running game
		else
		{
			sf::Vector2f mappos = TransformScreenToMap( mousepos );
			Object* obj = FindClickedObject( mappos );
			if ( obj )
			{
				switch ( obj->type )
				{
					case Object::CONVEYOR:
						{
							Conveyor& c = *(Conveyor*)obj;
							if ( c.isSwitch )
							{
								c.Switch();
								sndSwitch.Play();
							}
						}
						break;

					default:
						break;
				}
			}

			// Translate screen coordinates to level grid coordinates
/*			sf::Vector2f mappos = TransformScreenToMap( mousepos );
			Object* obj = level.GetObjectAt( (int)mappos.x, (int)mappos.y );
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
			}*/
		}
	} // end mouse down event

	//Compute
	if (isPaused == false)
	{
		level.Update();

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
						it = objects.erase( it ); // Remove pointer from vector
						--it;
						continue;
					}
					break;

				case Object::TRUCK:
					if ( DoTruck( *(Truck*)(*it) ) )
					{
						delete *it;
						it = objects.erase( it );
						--it;
						continue;
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

	// Timer
	if ( timer > 0 )
		--timer;

	// End game?
	if ( isGameOver and timer <= 0 )
	{
		EventMgr.PushEvent( ENGINE, GameEvent::ChangeSceneEvent( "highscore" ) );
		EventMgr.PushEvent( HIGHSCORE, GameEvent::HighscoreEvent( points ) );
	}

	// If we have a popup, center it
	if ( popup )
	{
		sf::Vector2f pos = popup->GetPosition();
		popup->SetPosition( pos.x, pos.y + ( App.GetHeight() / 2.0f - pos.y ) / 5.0f );
	}

	isMouseDown = newMouseButton;
	if ( level.levelTime >= 1 )
	{
	    level.levelTime -= 1;
    }
	// Out of time?
    if ( level.levelTime <= 0 )
    {
        isGameOver = true;
    }
    if ( level.levelTime == 100 * 10 )  // If there are only ten seconds left.
    {
        //Play running out of time sound.
    }
}

void SceneGame::Draw()
{
	//sf::Sprite bg( ResMgr.GetImage( "level background" ) );
	//bg.SetColor( sf::Color( 60, 60, 60 ) );
	//window->Draw( bg );
	App.GetWindow().Clear( sf::Color(100,100,100) );

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
					name << "conveyor " << (((Conveyor&)obj).isSwitchLeft ? obj.dir : ((obj.dir + 1) % 4)) << " turn";
					obj.sprite.SetImage( ResMgr.GetImage( name.str() ) );
				}

				// Not switch, is it turning or any other "odd" connection?
				else
				{
					std::stringstream name;
					name << "conveyor ";

					bool connections[4];
					connections[Dir::RIGHT] = level.GetObjectAt( (int)obj.pos.x + 1, (int)obj.pos.y ) != NULL;
					connections[Dir::UP] = level.GetObjectAt( (int)obj.pos.x, (int)obj.pos.y - 1 ) != NULL;
					connections[Dir::LEFT] = level.GetObjectAt( (int)obj.pos.x - 1, (int)obj.pos.y ) != NULL;
					connections[Dir::DOWN] = level.GetObjectAt( (int)obj.pos.x, (int)obj.pos.y + 1 ) != NULL;

					// Left turn (checking the directions on unit circle, only the one to the left of current dir should be connected)
					if ( connections[(obj.dir + 1) % 4] and !connections[(obj.dir + 2) % 4] and !connections[(obj.dir + 3) % 4] )
					{
						name << (obj.dir + 3) % 4 << " turn";
						obj.sprite.SetImage( ResMgr.GetImage( name.str() ) );
					}
					// Right turrn
					else if ( !connections[(obj.dir + 1) % 4] and !connections[(obj.dir + 2) % 4] and connections[(obj.dir + 3) % 4] )
					{
						name << (obj.dir + 2) % 4 << " turn";
						obj.sprite.SetImage( ResMgr.GetImage( name.str() ) );
					}

					// T junctions
					else if ( (obj.dir == Dir::RIGHT or obj.dir == Dir::LEFT) and connections[Dir::UP] )
					{
						name << "02 con 1";
						obj.sprite.SetImage( ResMgr.GetImage( name.str() ) );
					}
					else if ( (obj.dir == Dir::RIGHT or obj.dir == Dir::LEFT) and connections[Dir::DOWN] )
					{
						name << "02 con 3";
						obj.sprite.SetImage( ResMgr.GetImage( name.str() ) );
					}
					else if ( (obj.dir == Dir::UP or obj.dir == Dir::DOWN) and connections[Dir::LEFT] )
					{
						name << "13 con 2";
						obj.sprite.SetImage( ResMgr.GetImage( name.str() ) );
					}
					else if ( (obj.dir == Dir::UP or obj.dir == Dir::DOWN) and connections[Dir::RIGHT] )
					{
						name << "13 con 0";
						obj.sprite.SetImage( ResMgr.GetImage( name.str() ) );
					}

					// Cross junction
					else if ( connections[Dir::RIGHT] and connections[Dir::UP] and connections[Dir::LEFT] and connections[Dir::DOWN] )
					{
						if ( obj.dir == Dir::RIGHT or obj.dir == Dir::LEFT )
							name << "02 cross";
						else
							name << "13 cross";
						obj.sprite.SetImage( ResMgr.GetImage( name.str() ) );
					}
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
		App.GetWindow().Draw( obj.sprite );
	} // End loop through all objects

	App.GetWindow().Draw( pbuttonPause );
	if ( isPaused )
	{
		App.GetWindow().Draw( pbuttonQuit );
	}
	if ( popup )
		App.GetWindow().Draw( *popup );

	stringstream score;
	score << "Score: " << points;
	str_score.SetText(score.str());
	str_score.SetPosition( 10, 200 );
	App.GetWindow().Draw(str_score);
	stringstream time;
	time << "Time: " << (double)(level.levelTime / 100);
	str_time.SetText( time.str() );
	sf::FloatRect time_rect = str_time.GetRect();
	str_time.SetPosition( 320 - time_rect.GetWidth() - 10, 240 - time_rect.GetHeight() - 10 );
	App.GetWindow().Draw( str_time );
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
		(scaled.x) + 160,
		(scaled.y) + 120 );
	return screen;
}

float SceneGame::GetDistanceSQ( sf::Vector2f pos1, sf::Vector2f pos2 )
{
	sf::Vector2f diff( pos1.x - pos2.x, pos1.y - pos2.y );
	return diff.x * diff.x + diff.y * diff.y;
}

Object* SceneGame::FindClickedObject( sf::Vector2f& mappos )
{
	// Offset mouse coordinate by half, as tiles are placed center, while coords start upper left
	sf::Vector2f pos( mappos.x - .5f, mappos.y - .5f );
	float bestDistSQ = 3.5f * 3.5f;
	Object* res = NULL;
	for (std::list<Object*>::iterator it = clickables.begin(); it != clickables.end(); ++it )
	{
		float dist = GetDistanceSQ( pos, (**it).pos );
		if ( dist < bestDistSQ )
		{
			bestDistSQ = dist;
			res = (*it);
		}
	}
	return res;
}

// Return true if crate done and should be deleted
bool SceneGame::DoCrate( Crate& crate )
{
	// If crate.dest is ever NULL, then the level is messed up so just delete crate
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
						points += crate.value;
					}
					else
					{
						points -= crate.value;
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
			{
				crate.connected->connected = NULL;
				return true;
			}

			// Only go to next if next one is free
			if ( nextDest->connected == NULL )
			{
				crate.connected->connected = NULL; // Release conveyor we are standing on
				nextDest->connected = &crate; // Take the next one
				crate.connected = nextDest;
				distLeft -= curDist;
				if ( crate.connected->type == Object::CONVEYOR and ((Conveyor*)(crate.connected))->isSwitch == true )
                {
                    crate.value += 25;
                }
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
	if ( truck.active and truck.crates > 0 )
	{
		if ( truck.interval <= 0 and truck.targetpos.x == truck.pos.x and truck.targetpos.y == truck.pos.y )
		{
			truck.interval = truck.intervalmax;

			// Get random color
			objects.push_back( new Crate( truck.targetpos.x, truck.targetpos.y, truck.dir, level.GetRandomColor(), 0 ) );
			Crate& crate = *((Crate*)objects.back());

			// Assign first destination to get crate moving
			if ( truck.dir == Dir::RIGHT )
				crate.connected = level.GetObjectAt( (int)truck.targetpos.x + 1, (int)truck.targetpos.y );
			else if ( truck.dir == Dir::UP )
				crate.connected = level.GetObjectAt( (int)truck.targetpos.x, (int)truck.targetpos.y - 1 );
			else if ( truck.dir == Dir::LEFT )
				crate.connected = level.GetObjectAt( (int)truck.targetpos.x - 1, (int)truck.targetpos.y );
			else if ( truck.dir == Dir::DOWN )
				crate.connected = level.GetObjectAt( (int)truck.targetpos.x, (int)truck.targetpos.y + 1 );
            truck.crates -= 1;
            //printf( "Crates left: %i/%i\n", truck.crates, truck.craterevert );
		}
		truck.interval -= 1;
	}
	else
	{
	    if ( truck.crates > 0 and truck.delay <= 0 )
	    {
            if ( truck.dir == Dir::RIGHT )
            {
                truck.pos.x += truck.cdir;
            }
            else
            {
                truck.pos.y += truck.cdir;
            }
            if ( truck.pos.x >= truck.targetpos.x and truck.pos.y <= truck.targetpos.y )
            {
                truck.active = true;
                truck.pos.x = truck.targetpos.x;
                truck.pos.y = truck.targetpos.y;
            }
            // Play backing up sound
            //cout << "Parking...\n";
	    }
	    else if ( truck.delay <= 0 )
	    {
	        if ( truck.dir == Dir::RIGHT )
            {
                truck.pos.x -= truck.cdir;
                if ( truck.pos.x <= truck.targetpos.x - 5 and truck.pos.y == truck.targetpos.y )
                {
                    truck.delay = truck.delayrevert;
                    truck.pos.x = truck.targetpos.x - 5;
                    truck.pos.y = truck.targetpos.y;
                }
            }
            else
            {
                truck.pos.y -= truck.cdir;
                if ( truck.pos.x == truck.targetpos.x and truck.pos.y >= truck.targetpos.y + 5 )
                {
                    truck.delay = truck.delayrevert;
                    truck.pos.x = truck.targetpos.x;
                    truck.pos.y = truck.targetpos.y + 5;
                }
            }
            // Play driving away sound
            //cout << "Leaving...\n";
	    }
	    else
	    {
	        truck.delay -= 1;
            //printf( "Until new truck: %i/%i\n", truck.delay, truck.delayrevert );
            if ( truck.delay <= 0 )
            {
                truck.crates = truck.craterevert;
                truck.active = false;
                //cout << "New truck incoming!\n";
            }
	    }
	}
	return false;
}



// This makes sure the scene is added to the engine!
SceneGame* game = new SceneGame();
