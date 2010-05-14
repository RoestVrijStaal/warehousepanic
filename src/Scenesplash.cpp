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
	presenters.push_back( new Text( "Game Design Novice", 58, 100, Text::MEDIUM ) );
	presenters.push_back( new Text( "presents", 124, 130, Text::SMALL ) );
	presenters.push_back( new Text( "a P.A.C.C. February 2010 entry", 6, App.GetHeight() - 16, Text::SMALL ) );
	presenters.push_back( new Text( "v1.0", 0, 0, Text::SMALL ) );
	presenters.back()->SetPosition( App.GetWidth() - presenters.back()->GetWidth() - 6, App.GetHeight() - 16 );
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
