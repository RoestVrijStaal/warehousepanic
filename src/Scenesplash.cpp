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
	presenters.push_back( new Text( "Game Design Novice", 68, 100, Text::MEDIUM ) );
	presenters.push_back( new Text( "presents", 125, 130, Text::SMALL ) );
}

void SceneSplash::Terminate()
{
	background = gdn::Sprite();

	for ( std::vector< Text* >::iterator it = presenters.begin(); it != presenters.end(); ++it )
	{
		delete *it;
	}
	presenters.clear();
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

	for ( std::vector< Text* >::iterator it = presenters.begin(); it != presenters.end(); ++it )
	{
		(**it).Draw();
	}
}



SceneSplash* splash = new SceneSplash();
