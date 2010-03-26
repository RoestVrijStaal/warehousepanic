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
	background = gdn::Sprite( ResMgr.GetImage( "splash" ) );
}

void SceneSplash::Terminate()
{
	background = gdn::Sprite();
}

void SceneSplash::Step()
{
	++time;

	bool isMouseDown = App.GetWindow().IsMouseButtonDown();
	if ( isMouseDown and time > MIN_SPLASH_TIME )
	{
		EventMgr.PushEvent( gdn::ENGINE, gdn::GameEvent::ChangeSceneEvent( "menu" ) );
	}
}

void SceneSplash::Draw()
{
	App.GetWindow().Draw( background );
}



SceneSplash* splash = new SceneSplash();
