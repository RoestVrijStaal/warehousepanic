#include "SceneCredits.h"



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

	AddText( "CREDITS", Text::LARGE );
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
	AddText( "Shawn Hartnell", Text::SMALL );
	AddText( "Chase Warrington", Text::SMALL );
	AddText( "Uni Dahl", Text::SMALL );
	AddText( "Fonts", Text::MEDIUM );
	AddText( "Yoinks by A.J. Palmer", Text::SMALL );
	AddText( "Sound Effects", Text::MEDIUM );
	AddText( "soundjay.com", Text::SMALL );
	AddText( "Menu Music", Text::MEDIUM );
	AddText( "Mike Koenig free-loops.com", Text::SMALL );
	AddText( "Highscore Music", Text::MEDIUM );
	AddText( "Dfrltiger free-loops.com", Text::SMALL );
	AddText( "Game Music", Text::MEDIUM );
	AddText( "Mike Koenig free-loops.com", Text::SMALL );
	AddText( "", Text::MEDIUM );
	AddText( "A big shout-out", Text::SMALL );
	AddText( "to the GP32X community", Text::SMALL );
	AddText( "and all the sponsors", Text::SMALL );
	AddText( "", Text::MEDIUM );
	AddText( "Thank you for playing", Text::MEDIUM );
	AddText( "Visit us at", Text::CNTR_MEDIUM );
	// Exclamation marks show up as slashes
	// Also, underscores are colons
	AddText( "http_!!cpp.wikicomplete.info", Text::CNTR_SMALL );
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

void SceneCredits::AddText( std::string text, Text::Size size )
{
	// Calculate position
	float curPos = ( credits.size() == 0 ? App.GetHeight() : credits.back()->GetPosition().y );
	float xOffset = 0;
	switch ( size )
	{
		case Text::SMALL: curPos += 25.0f; break;
		case Text::MEDIUM: curPos += 50.0f; xOffset = -60.0f; break;
		case Text::LARGE: curPos += 10.0f; break;
		case Text::CNTR_MEDIUM: curPos += 50.0f; break;
		case Text::CNTR_SMALL: curPos += 25.0f; xOffset = -50.0f; break;
		default: break;
	}

	Text& t = *(new Text( text ));
	credits.push_back( &t );
	t.SetPosition( App.GetWidth() / 2.0f - (t.GetWidth() / 2.0f) - 35.0f + xOffset, curPos );
	t.SetSize( size );
}



// This makes sure the scene is added to the engine!
SceneCredits* credits = new SceneCredits();
