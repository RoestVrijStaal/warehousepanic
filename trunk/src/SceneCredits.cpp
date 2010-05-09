#include "SceneCredits.h"
#include <iostream>
using namespace std;


SceneCredits::SceneCredits() : Scene( "credits" )
{
}

SceneCredits::~SceneCredits()
{
}

void SceneCredits::Initialize()
{
	curOffset = 0;
	isMouseDown = true;

	bg_general = gdn::Sprite( ResMgr.GetImage( "general" ) );

	AddText( "CREDITS", Text::LARGE, true );
	AddText( "", Text::MEDIUM );
	AddText( "Producer", Text::MEDIUM );
	AddText( "Uni Dahl", Text::SMALL );
	AddText( "Game Design", Text::MEDIUM );
	AddText( "GDN community", Text::SMALL );
	AddText( "Game Programmer", Text::MEDIUM );
	AddText( "Chase Warrington", Text::SMALL );
	AddText( "Engine Programmer", Text::MEDIUM );
	AddText( "Uni Dahl", Text::SMALL );
	AddText( "Graphics", Text::MEDIUM );
	AddText( "mr glasses", Text::SMALL );
	AddText( "Concept artist", Text::MEDIUM );
	AddText( "Shawn Hartnell", Text::SMALL );
	AddText( "Fonts", Text::MEDIUM );
	AddText( "WC Wunderbach Mix", Text::SMALL );
	AddText( "http://www.wcfonts.com", Text::SMALL );
	AddText( "Sound Effects", Text::MEDIUM );
	AddText( "soundjay.com", Text::SMALL );
	AddText( "soundbible.com", Text::SMALL );
	AddText( "free-loops.com", Text::SMALL );
	AddText( "Menu Music", Text::MEDIUM );
	AddText( "Mike Koenig free-loops.com", Text::SMALL );
	AddText( "Highscore Music", Text::MEDIUM );
	AddText( "Dfrltiger free-loops.com", Text::SMALL );
	AddText( "Game Music", Text::MEDIUM );
	AddText( "Mike Koenig free-loops.com", Text::SMALL );
	AddText( "", Text::MEDIUM );
	AddText( "Special thanks to", Text::MEDIUM, true );
	AddText( "Iorgy77 for organizing PACC", Text::SMALL, true );
	AddText( "Anyone who provided feedback", Text::SMALL, true );
	AddText( "Everyone who participated", Text::SMALL, true );
	AddText( "All the sponsors", Text::SMALL, true );
	AddText( "", Text::MEDIUM );
	AddText( "And a big shout-out to", Text::SMALL, true );
	AddText( "the GP32X community", Text::SMALL, true );
	AddText( "", Text::MEDIUM );
	AddText( "Thank you for playing", Text::MEDIUM, true );
	AddText( "Visit us at", Text::MEDIUM, true );
	AddText( "http://warehousepanic.googlecode.com", Text::SMALL, true );
}

void SceneCredits::Terminate()
{
	for ( std::vector< Text* >::iterator it = credits.begin(); it != credits.end(); ++it )
		delete (*it);
	credits.clear();
}

void SceneCredits::Step()
{
	bool curMouseDown = App.GetWindow().IsMouseButtonDown();
	if ( curMouseDown and !isMouseDown ) // Mouse down event
	{
		EventMgr.PushEvent( gdn::ENGINE, gdn::GameEvent::QuitEvent() );
	}
	isMouseDown = curMouseDown;

	if ( credits.back()->GetPosition().y > App.GetHeight() / 2 )
	{
		for (std::vector< Text* >::iterator it = credits.begin(); it != credits.end(); ++it )
		{
			const gdn::Vector2f& pos = (**it).GetPosition();
			(**it).SetPosition( pos.x, pos.y - 0.3f );
		}
		curOffset = 0.3f;
	}
}

void SceneCredits::Draw()
{
	App.GetWindow().Clear( 0, 0, 0 );

    App.GetWindow().Draw( bg_general );

	for (std::vector< Text* >::iterator it = credits.begin(); it != credits.end(); ++it )
	{
		float pos = (**it).GetPosition().y;

		if ( pos > -40 and pos < App.GetHeight() )
		{
			(**it).Draw();
		}
	}
}

void SceneCredits::AddText( std::string text, Text::Size size, bool isCenter )
{
	// Calculate position
	float curPos = ( credits.size() == 0 ? App.GetHeight() : credits.back()->GetPosition().y );

	float xPos; // Used when not centering
	switch ( size )
	{
		case Text::SMALL: curPos += 25.0f; xPos = 110; break;
		case Text::MEDIUM: curPos += 50.0f; xPos = 70; break;
		case Text::LARGE: curPos += 10.0f; xPos = 30; break;
		default: break;
	}

	Text& t = *(new Text( text ));
	credits.push_back( &t );
	t.SetSize( size );

	if ( isCenter )
	{
		t.SetPosition( App.GetWidth() / 2.0f - t.GetWidth() / 2.0f, curPos );
	}
	else
	{
		t.SetPosition( xPos, curPos );
	}
}



// This makes sure the scene is added to the engine!
SceneCredits* credits = new SceneCredits();
