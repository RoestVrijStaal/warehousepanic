#include "Scenesplash.h"



SceneSplash::SceneSplash() : Scene( "splash" )
{
}

SceneSplash::~SceneSplash()
{
}

void SceneSplash::Initialize()
{
	time = 0;
	background = sf::Sprite( ResMgr.GetImage( "splash" ) );
}

void SceneSplash::Terminate()
{
	background = sf::Sprite();
}

void SceneSplash::Step()
{
	++time;

	bool isMouseDown = App.GetWindow().GetInput().IsMouseButtonDown( sf::Mouse::Left );
	if ( isMouseDown and time > MIN_SPLASH_TIME )
	{
		EventMgr.PushEvent( ENGINE, GameEvent::ChangeSceneEvent( "menu" ) );
	}
}

void SceneSplash::Draw()
{
	App.GetWindow().Draw( background );
}



SceneSplash* splash = new SceneSplash();
