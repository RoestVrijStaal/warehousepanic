#include "SceneHighscore.h"

#include "WCEngine/Application.h"
#include "WCEngine/EventManager.h"
#include "WCEngine/ResourceManager.h"



// Constructors
SceneHighscore::SceneHighscore() : Scene( "highscore" )
{
}

SceneHighscore::~SceneHighscore()
{
}



// Methods
void SceneHighscore::Initialize()
{
	isMouseDown = true;
	keyboard = NULL;
	newScore = 0;
	name = "";

	// Any event for highscore scene?
	while ( EventMgr.HasEvent( HIGHSCORE ) )
	{
		GameEvent& event = EventMgr.PeekEvent( HIGHSCORE );
		switch ( event.type )
		{
			case GameEvent::Highscore:
				// Reached highscore table from game, so play gameover music
				ResMgr.GetMusic( "game over" ).Play();
				newScore = event.Highscore_new_score;
				// TODO: If we reach highscore then show keyboard
				if ( newScore )
				{
					keyboard = new Keyboard();
					keyboard->Show();
				}
				break;

			default:
				break;
		}
		EventMgr.PopEvent( HIGHSCORE );
	}
}

void SceneHighscore::Terminate()
{
	if ( keyboard )
		delete keyboard;
	keyboard = NULL;
	ResMgr.GetMusic( "game over" ).Stop();
}

void SceneHighscore::Step()
{
	if ( keyboard )
	{
		keyboard->Step();
		if ( keyboard->IsShown() )
		{
			// User pressed enter?
			if ( keyboard->IsDone() )
			{
				name = keyboard->GetText();
				keyboard->Hide();
				isMouseDown = true;
			}
		}
	}

	// Ignore everything if keyboard is shown
	if ( keyboard == NULL or !keyboard->IsShown() )
	{
		bool curMouseDown = App.GetWindow().GetInput().IsMouseButtonDown( sf::Mouse::Left );
		if ( curMouseDown and !isMouseDown )
		{
			EventMgr.PushEvent( ENGINE, GameEvent::ChangeSceneEvent( "menu" ) );
		}
		isMouseDown = curMouseDown;
	}
}

void SceneHighscore::Draw()
{
	App.GetWindow().Clear( sf::Color( 0, 0, 0 ) );
	sf::String str( std::string("Highscore ").append( name ), sf::Font::GetDefaultFont(), 12 );
	str.SetPosition( 10, 60 );
	App.GetWindow().Draw( str );

	if ( keyboard )
		keyboard->Draw();
}



// This makes sure the scene is added to the engine!
SceneHighscore* highscore = new SceneHighscore();
