#include "SceneGame.h"


#include <iostream>
#include <sstream>
#include <cmath>
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
	std::stringstream levelname;
	points = 0;
	while ( EventMgr.HasEvent( gdn::GAME ) )
	{
		gdn::GameEvent& event = EventMgr.PeekEvent( gdn::GAME );
		switch ( event.type )
		{
			case gdn::GameEvent::ChangeScore:
				points = event.ChangeLevel_the_score;
				break;

			case gdn::GameEvent::ChangeLevel:
				curLevel = event.ChangeLevel_next_level;
				levelname << "levels/" << curLevel << ".lvl";
				break;

			default:
				break;
		}
		EventMgr.PopEvent( gdn::GAME );
	}

	// Level stuff
	level = Level( levelname.str() ); // TODO: How do we choose level?
	if ( level.objects.size() == 0 )
	{
		// Go to highscores
		EventMgr.PushEvent( gdn::ENGINE, gdn::GameEvent::ChangeSceneEvent( "highscore" ) );
		EventMgr.PushEvent( gdn::HIGHSCORE, gdn::GameEvent::HighscoreEvent( points ) );
	}
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
				Conveyor& c = *(Conveyor*)(*it);
				if ( c.isSwitch )
				{
					clickables.push_back( *it );
				}
			}
		}
	}

	// Buttons
	pbuttonPause = gdn::Sprite( ResMgr.GetImage( "button pause" ) );
	pbuttonPause.SetCenter( pbuttonPause.GetImage()->GetWidth() / 2.0f, pbuttonPause.GetImage()->GetHeight() / 2.0f );
	pbuttonPause.SetPosition(
		App.GetWidth() - pbuttonPause.GetImage()->GetWidth() / 2.0f - 5,
		pbuttonPause.GetImage()->GetWidth() / 2.0f + 5 ); // Top right corner
	pbuttonQuit = gdn::Sprite( ResMgr.GetImage( "button quit" ) );
	pbuttonQuit.SetCenter( pbuttonQuit.GetImage()->GetWidth() / 2.0f, pbuttonQuit.GetImage()->GetHeight() / 2.0f );
	pbuttonQuit.SetPosition(
		App.GetWidth() - pbuttonPause.GetImage()->GetWidth() - pbuttonQuit.GetImage()->GetWidth() / 2.0f - 10,
		pbuttonQuit.GetImage()->GetHeight() / 2.0f + 5 ); // Top right corner next to pause button
	// We assign a new sprite to popup when we have some popup to display
	popup = NULL;
	background = gdn::Sprite( ResMgr.GetImage( "level" ) );

	// Click animation
	click = gdn::Animation();
	click.SetLoop( false );
	click.SetSpeed( 0.5f );
	for ( int frameidx = 1; frameidx <= 10; ++frameidx )
	{
		std::stringstream name;
		name << "click " << frameidx;
		click.AddFrame( ResMgr.GetImage( name.str() ) );
	}
	click.SetCenter( click.GetImage()->GetWidth() / 2, click.GetImage()->GetHeight() / 2 );

	// Lost crates placeholders
	for ( int i = 0; i < NUM_CRATES; ++i )
	{
		stars.push_back( new Star( ResMgr.GetImage( "life shadow" ), ResMgr.GetImage( "life shadow" ).GetWidth() / 2, ResMgr.GetImage( "life shadow" ).GetHeight(), false ) );
		stars.back()->target = gdn::Vector2f( App.GetWidth() - 100 + i * 18, App.GetHeight() );
		stars.back()->pos = stars.back()->target;
		stars.back()->vel.x = stars.back()->vel.y = 0.0f;
		stars.back()->delay = 0;
	}

	// Sounds
	sndSwitch = gdn::Sound( ResMgr.GetSound( "switch" ) );
	sndClick = gdn::Sound( ResMgr.GetSound( "click" ) );
	sndCrate = gdn::Sound( ResMgr.GetSound( "crate" ) );
	sndBack = gdn::Sound( ResMgr.GetSound( "back" ) );
	sndDrive = gdn::Sound( ResMgr.GetSound( "drive" ) );
	sndPoint = gdn::Sound( ResMgr.GetSound( "point" ) );
	sndLife = gdn::Sound( ResMgr.GetSound( "life" ) );
	sndWin = gdn::Sound( ResMgr.GetSound( "win" ) );
	sndFail = gdn::Sound( ResMgr.GetSound( "fail" ) );

	//Other stuff
	isMouseDown = false;
	isPaused = false;
	isGameOver = false;
	didWin = true;
	didQuit = false;
	justStopped = false;
	sound = false;
	timer = 0;
	cratesLost = 0;

	str_score.SetSize( Text::MEDIUM );
	str_score.SetPosition( 5, App.GetHeight() - 23 );
	//str_time.SetSize( Text::MEDIUM );

	ResMgr.GetMusic( "game" ).Play();
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

	for ( std::list<Star*>::iterator it = stars.begin(); it != stars.end(); ++it )
		delete *it;
	stars.clear();

	ResMgr.GetMusic( "game" ).Stop();
}

void SceneGame::Step()
{
    if ( cratesLost >= NUM_CRATES and !isGameOver )
    {
        isGameOver = true;
        //level.levelTime = 0;
        didQuit = false;
        didWin = false;
        timer = (int)(App.GetFPS() * 3);
        justStopped = true;
    }
	//Events
	gdn::Vector2f mousepos( App.GetWindow().GetMouseX(), App.GetWindow().GetMouseY() );
	bool newMouseButton = App.GetWindow().IsMouseButtonDown();

	// Handle mouse-down event
	if (newMouseButton and isMouseDown == false)
	{
		// If squared distance to button center is < then size of button squared, then we clicked inside it
		if ( GetDistanceSQ(mousepos, pbuttonPause.GetPosition()) < pbuttonPause.GetImage()->GetWidth() / 2.0f * pbuttonPause.GetImage()->GetWidth() / 2.0f )
		{
			sndClick.Play();
			isPaused = !isPaused;
			if ( isPaused and !isGameOver )
			{
				pbuttonPause.SetImage( ResMgr.GetImage( "button pause active" ) );

				if ( popup )
					delete popup;
				popup = new gdn::Sprite( ResMgr.GetImage( "text paused" ) );
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
		if ( isPaused and !isGameOver )
		{
			// Clicked inside quit button?
			if ( GetDistanceSQ(mousepos, pbuttonQuit.GetPosition()) < pbuttonQuit.GetImage()->GetWidth() / 2.0f * pbuttonQuit.GetImage()->GetWidth() / 2.0f )
			{
				sndClick.Play();
                timer = 50;
				pbuttonQuit.SetImage( ResMgr.GetImage( "button quit active" ) );
				justStopped = false;
				didQuit = true;
				didWin = false;
				isGameOver = true;
			}

		}

		// Mouse down event, running game
		else
		{
			Object* obj = FindClickedObject( mousepos );
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
								click.SetPosition( TransformMapToScreen( c.pos ) );
								click.Play();
								sndSwitch.Play();
							}
						}
						break;

					default:
						break;
				}
			}
		}
	} // end mouse down event

	//Compute
	if (isPaused == false and !isGameOver )
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
	} // Game not paused

	// Timer
	if ( timer > 0 )
	{
		--timer;
	}

	// Move the stars
	for ( std::list<Star*>::iterator it = stars.begin(); it != stars.end(); ++it )
	{
		Star& star = (**it);
		gdn::Vector2f diff( star.target.x - star.pos.x, star.target.y - star.pos.y );

		if ( star.willRemove and diff.x * diff.x + diff.y * diff.y < 10 * 10 )
		{
			delete *it;
			it = stars.erase( it );
		}
		else
		{
			if ( star.delay <= 0 )
			{
				float factor = 500;
				if ( !star.willRemove )
					factor = 100;
				star.vel.x += diff.x / factor;
				star.vel.y += diff.y / factor;
			}
			else
			{
				--star.delay;
			}

			float drag = 0.95f;
			if ( !star.willRemove )
				drag = 0.85f;

			star.vel.x *= drag;
			star.vel.y *= drag;

			star.pos.x += star.vel.x;
			star.pos.y += star.vel.y;

			if ( fabs( star.pos.x - star.target.x ) < 0.5f and fabs( star.pos.y - star.target.y ) < 0.5f )
			{
				star.pos.x = star.target.x;
				star.pos.y = star.target.y;
			}
		}
	}

	// End game?
	if ( isGameOver and timer <= 0 and /*level.levelTime <= 0 and*/ !justStopped and !didQuit )
	{
	    if ( didWin )
	    {
            EventMgr.PushEvent( gdn::ENGINE, gdn::GameEvent::ChangeSceneEvent( "game" ) );
            EventMgr.PushEvent( gdn::GAME, gdn::GameEvent::ChangeLevelEvent( curLevel + 1 ) );
				EventMgr.PushEvent( gdn::GAME, gdn::GameEvent::ChangeScoreEvent( points ) );
	    }
	    else
	    {
            EventMgr.PushEvent( gdn::ENGINE, gdn::GameEvent::ChangeSceneEvent( "highscore" ) );
            EventMgr.PushEvent( gdn::HIGHSCORE, gdn::GameEvent::HighscoreEvent( points ) );
	    }
	}
	else if ( isGameOver and justStopped and /*level.levelTime <= 0 and*/ !didQuit )
	{
		ResMgr.GetMusic( "game" ).Stop();
	    if ( didWin )
	    {
	        if ( !sound )
	        {
                sndWin.Play();
                sound = true;
	        }
	        if ( popup )
                    delete popup;
            popup = new gdn::Sprite( ResMgr.GetImage( "text win" ) );
            popup->SetCenter( popup->GetImage()->GetWidth() / 2.0f, popup->GetImage()->GetHeight() / 2.0f );
            popup->SetPosition( (float)App.GetWidth() / 2.0f, -(float)(popup->GetImage()->GetHeight()) / 2.0f ); // At top of screen (to animate falling down)
            justStopped = false;
	    }
	    else
	    {
	        if ( !sound )
	        {
                sndFail.Play();
                sound = true;
	        }
	        if ( popup )
                    delete popup;
            popup = new gdn::Sprite( ResMgr.GetImage( "text fail" ) );
            popup->SetCenter( popup->GetImage()->GetWidth() / 2.0f, popup->GetImage()->GetHeight() / 2.0f );
            popup->SetPosition( (float)App.GetWidth() / 2.0f, -(float)(popup->GetImage()->GetHeight()) / 2.0f ); // At top of screen (to animate falling down)
            justStopped = false;
	    }
	}
	/*else if ( level.levelTime <= 0 and !isGameOver and !didQuit )
	{
	    isGameOver = true;
	    didWin = false;
        timer = (int)(App.GetFPS() * 3);
	}*/
	else if ( timer <= 0 and didQuit )
	{
        EventMgr.PushEvent( gdn::ENGINE, gdn::GameEvent::ChangeSceneEvent( "highscore" ) );
        EventMgr.PushEvent( gdn::HIGHSCORE, gdn::GameEvent::HighscoreEvent( points ) );
	}

	// If we have a popup, center it
	if ( popup )
	{
		gdn::Vector2f pos = popup->GetPosition();
		popup->SetPosition( pos.x, pos.y + ( App.GetHeight() / 2.0f - pos.y ) / 8.0f );
	}

	isMouseDown = newMouseButton;
	/*if ( level.levelTime >= 1 and !isPaused )
	{
	    level.levelTime -= 1;
    }
	// Out of time?
    if ( level.levelTime <= 0 and justStopped )
    {
        isGameOver = true;
        didWin = false;
        timer = (int)(App.GetFPS() * 3);
    }*/
    if ( level.amountOfTrucks <= 0 /*and level.levelTime > 0*/ )
    {
        bool crateLeft = false;
        for ( std::list<Object*>::iterator it = objects.begin(); it != objects.end(); ++it )
        {
            if ( crateLeft )
                break;
            Object& obj = (**it);
            switch ( obj.type )
            {
                case Object::CRATE:
                    crateLeft = true;
                    break;

                case Object::GATE:
                case Object::GATE_BACKGROUND:
                case Object::INCINERATOR:
                case Object::TRUCK:
                default:
                    break;
            }
        }
        if ( !crateLeft and level.amountOfTrucks <= 0 and !isGameOver )
        {
            isGameOver = true;
            justStopped = true;
            //level.levelTime = 0;
            didQuit = false;
            timer = (int)(App.GetFPS() * 3);
            didWin = true;
        }
    }
    /*if ( level.levelTime == 100 * 10 )  // If there are only ten seconds left.
    {
        //Play running out of time sound.
    }*/

}

void SceneGame::Draw()
{
	//sf::Sprite bg( ResMgr.GetImage( "level background" ) );
	//bg.SetColor( sf::Color( 60, 60, 60 ) );
	//window->Draw( bg );
	App.GetWindow().Draw( background );
	//App.GetWindow().Clear( 70, 70, 70 );

	// Draw all objects
	for ( std::list<Object*>::iterator it = objects.begin(); it != objects.end(); ++it )
	{
		Object& obj = (**it);
		gdn::Vector2f screenPos = TransformMapToScreen( obj.pos );
		switch ( obj.type )
		{
			case Object::CRATE:
				obj.sprite.SetPosition( screenPos.x, screenPos.y - 5 ); // Draw atop conveyor
				break;

			case Object::TRUCK:
				// Offset truck by one square (diff between graphics and logic)
				if ( obj.dir == Dir::UP )
				{
					gdn::Vector2f pos( obj.pos.x, obj.pos.y + 1.0f );
					screenPos = TransformMapToScreen( pos );
				}
				obj.sprite.SetPosition( screenPos );
				break;

			// Conveyors are special. They need to draw the correct branching sprite
			case Object::CONVEYOR:
				if ( ((Conveyor&)obj).isSwitch )
				{
					std::stringstream name;
					name << "conveyor " << (((Conveyor&)obj).isSwitchLeft ? obj.dir : ((obj.dir + 1) % 4)) << " turn";

					// Help for first players
					if ( not ( curLevel == 1 and level.curTime < App.GetFPS() * 5 and (level.curTime / 20) % 2 == 0 ) )
					{
						name << " high";
					}
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
			default:
				obj.sprite.SetPosition( screenPos );
				break;
		}
		App.GetWindow().Draw( obj.sprite );
	} // End loop through all objects

	// Draw the stars
	for ( std::list<Star*>::iterator it = stars.begin(); it != stars.end(); ++it )
	{
		Star& star = (**it);
		star.sprite.SetPosition( star.pos.x, star.pos.y );
		App.GetWindow().Draw( star.sprite );
	}

	App.GetWindow().Draw( pbuttonPause );
	if ( isPaused )
	{
		App.GetWindow().Draw( pbuttonQuit );
	}
	if ( popup )
		App.GetWindow().Draw( *popup );

	if ( click.IsPlaying() )
		App.GetWindow().Draw( click );

	/*stringstream time;
	time << "TIME   " << (level.levelTime / App.GetFPS());
	str_time.SetText( time.str() );
	str_time.SetPosition( 5, 197 );
	str_time.Draw();*/
	stringstream score;
	score << "SCORE   " << points;
	str_score.SetText( score.str() );
	str_score.Draw();
}



// Helper functions
#define TILE_SIZE 40
gdn::Vector2f SceneGame::TransformScreenToMap( gdn::Vector2f& pos )
{
	gdn::Vector2f center(
		pos.x + 10 * TILE_SIZE / 2,
		pos.y - 12 * TILE_SIZE / 4);

	gdn::Vector2f map(
		center.x * 1 / TILE_SIZE + center.y * 2 / -TILE_SIZE,
		center.x * 1 / TILE_SIZE + center.y * 2 / TILE_SIZE );
	return map;
}

gdn::Vector2f SceneGame::TransformMapToScreen( gdn::Vector2f& pos )
{
	gdn::Vector2f screen(
		pos.x * TILE_SIZE / 2 + pos.y * TILE_SIZE / 2 - 10 * TILE_SIZE / 2,
		pos.x * -TILE_SIZE / 4 + pos.y * TILE_SIZE / 4 + 12 * TILE_SIZE / 4 );
	return screen;
}

float SceneGame::GetDistanceSQ( gdn::Vector2f& pos1, gdn::Vector2f& pos2 )
{
	gdn::Vector2f diff( pos1.x - pos2.x, pos1.y - pos2.y );
	return diff.x * diff.x + diff.y * diff.y;
}

Object* SceneGame::FindClickedObject( gdn::Vector2f& screenpos )
{
	// Offset mouse coordinate by half, as tiles are placed center, while coords start upper left
	Object* res = NULL;
	float bestDistSQ = 30 * 30; // Max click distance
	for (std::list<Object*>::iterator it = clickables.begin(); it != clickables.end(); ++it )
	{
		gdn::Vector2f curPos = TransformMapToScreen( (**it).pos );
		float dist = GetDistanceSQ( curPos, screenpos );
		if ( dist < bestDistSQ )
		{
			res = (*it);
			bestDistSQ = dist;
		}
	}

/*	gdn::Vector2f pos( mappos.x - .5f, mappos.y - .5f );
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
	}*/
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
					{
						Conveyor& c = *(Conveyor*)(crate.connected);
						crate.dir = c.GetCurDirection();
					}
					break;

				// We landed on gate, so break link between gate and crate
				case Object::GATE:
					if ( crate.color == crate.connected->color )
					{
						points += crate.value;
						// Create star(s), because we got points
						int starAmount = crate.value / 8 + 4;
						for ( int i = 0; i < starAmount; i++ )
						{
							stars.push_back( new Star( ResMgr.GetImage( "star" ), ResMgr.GetImage( "star" ).GetWidth() / 2, ResMgr.GetImage( "star" ).GetHeight() / 2 ) );
							stars.back()->target = gdn::Vector2f( str_score.GetPosition().x + str_score.GetWidth(), str_score.GetPosition().y );
							stars.back()->pos = TransformMapToScreen( crate.pos );
							stars.back()->vel.x = (float)((rand() % 10) - 5) / 2.0f;
							stars.back()->vel.y = (float)((rand() % 10) - 5) / 2.0f;
							stars.back()->delay = rand() % 40;
						}
                        sndPoint.Play();
					}
					else
					{
						++cratesLost;
						stars.push_back( new Star( ResMgr.GetImage( "life" ), 20, ResMgr.GetImage( "life" ).GetHeight() - 10, false ) );
						stars.back()->target = gdn::Vector2f( App.GetWidth() - 100 + (cratesLost-1) * 18, App.GetHeight() - 12 );
						stars.back()->pos = TransformMapToScreen( crate.pos );
						stars.back()->pos.y -= 5; // Crates are drawn 5 pixels above conveyor
						stars.back()->vel.x = stars.back()->vel.y = 0.0f;
						stars.back()->delay = 100;
						sndLife.Play();
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

				// Only add points first time switch is visited
				if ( crate.connected->type == Object::CONVEYOR
					and ((Conveyor*)(crate.connected))->isSwitch == true
					and crate.visited.find( level.GetIndex( (int)crate.connected->pos.x, (int)crate.connected->pos.y ) ) == crate.visited.end() )
				{
					crate.value += 25;

					// Mark this switch so it doesn't get counted again
					crate.visited.insert( level.GetIndex( (int)crate.connected->pos.x, (int)crate.connected->pos.y ) );
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
			gdn::Vector2f diff( crate.connected->pos.x - crate.pos.x, crate.connected->pos.y - crate.pos.y );
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
	    truck.soundPlaying = false;
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

            sndCrate.Play();
		}
		truck.interval -= 1;
	}
	else
	{
	    if ( truck.crates > 0 and truck.delay <= 0 and level.amountOfTrucks > 0 )
	    {
            if ( truck.dir == Dir::RIGHT )
            {
                truck.pos.x += truck.cdir;
                if ( !truck.soundPlaying )
                {
                    truck.soundPlaying = true;
                    sndBack.Play();
                }
            }
            else
            {
                truck.pos.y += truck.cdir;
                if ( !truck.soundPlaying )
                {
                    truck.soundPlaying = true;
                    sndBack.Play();
                }
            }
            if ( truck.pos.x >= truck.targetpos.x and truck.pos.y <= truck.targetpos.y )
            {
                truck.active = true;
                truck.pos.x = truck.targetpos.x;
                truck.pos.y = truck.targetpos.y;
            }
	    }
	    else if ( truck.delay <= 0 )
	    {
	        if ( truck.dir == Dir::RIGHT and level.amountOfTrucks > 0 )
            {
                truck.pos.x -= truck.cdir;
                if ( truck.pos.x <= truck.targetpos.x - 7 and truck.pos.y == truck.targetpos.y )
                {
                    truck.delay = truck.delayrevert;
                    truck.pos.x = truck.targetpos.x - 7;
                    truck.pos.y = truck.targetpos.y;
                }
                if ( !truck.soundPlaying )
                {
                    truck.soundPlaying = true;
                    sndDrive.Play();
                }
            }
            else
            {
                truck.pos.y -= truck.cdir;
                if ( truck.pos.x == truck.targetpos.x and truck.pos.y >= truck.targetpos.y + 7 )
                {
                    truck.delay = truck.delayrevert;
                    truck.pos.x = truck.targetpos.x;
                    truck.pos.y = truck.targetpos.y + 7;
                }
                if ( !truck.soundPlaying )
                {
                    truck.soundPlaying = true;
                    sndDrive.Play();
                }
            }

	    }
	    else if ( level.amountOfTrucks > 0 )
	    {
	        truck.delay -= 1;
            if ( truck.delay <= 0 )
            {
                truck.crates = truck.craterevert;
                truck.active = false;
                truck.soundPlaying = false;
                level.amountOfTrucks -= 1;
            }
	    }
	}
	return false;
}



// This makes sure the scene is added to the engine!
SceneGame* game = new SceneGame();
