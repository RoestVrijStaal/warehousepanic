#include "SceneHighscore.h"

#include "WCEngine/Application.h"
#include "WCEngine/EventManager.h"
#include "WCEngine/ResourceManager.h"



// Constructors
SceneHighscore::SceneHighscore() : Scene( "highscore" )
{
	App.AddScene( this );
}

SceneHighscore::~SceneHighscore()
{
}



// Methods
void SceneHighscore::Initialize()
{
	isMouseDown = true;
}

void SceneHighscore::Terminate()
{
}

void SceneHighscore::Step()
{
	bool curMouseDown = App.GetWindow().GetInput().IsMouseButtonDown( sf::Mouse::Left );
	if ( curMouseDown and !isMouseDown )
	{
		EventMgr.PushEvent( ENGINE, GameEvent::ChangeSceneEvent( "menu" ) );
	}

	isMouseDown = curMouseDown;
}

void SceneHighscore::Draw()
{
	App.GetWindow().Clear( sf::Color( 0, 0, 0 ) );
	sf::String str( "Highscore", sf::Font::GetDefaultFont(), 12 );
	str.SetPosition( 10, 60 );
	App.GetWindow().Draw( str );
}



// This makes sure the scene is added to the engine!
SceneHighscore* highscore = new SceneHighscore();
