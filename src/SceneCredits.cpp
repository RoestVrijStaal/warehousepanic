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
	AddText( "Chase Warrington", Text::SMALL );
	AddText( "Uni Dahl", Text::SMALL );
	AddText( "Sound Effects", Text::MEDIUM );
	AddText( "...", Text::SMALL );
	AddText( "Menu Music by", Text::MEDIUM );
	AddText( "...", Text::SMALL );
	AddText( "Highscore Music by", Text::MEDIUM );
	AddText( "...", Text::SMALL );
	AddText( "Game Music by", Text::MEDIUM );
	AddText( "...", Text::SMALL );
	AddText( "Thank you for playing", Text::SMALL );
	AddText( "Visit us at", Text::SMALL );
	AddText( "http://cpp.wikicomplete.info", Text::SMALL );
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

	for (std::vector< Text* >::iterator it = credits.begin(); it != credits.end(); ++it )
	{
		const gdn::Vector2f& pos = (**it).GetPosition();
		(**it).SetPosition( pos.x, pos.y - 0.5f );
	}
	curOffset = 0.5f;
}

void SceneCredits::Draw()
{
	App.GetWindow().Clear( 0, 0, 0 );

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
	switch ( size )
	{
		case Text::SMALL: curPos += 25.0f; break;
		case Text::MEDIUM: curPos += 50.0f; break;
		case Text::LARGE: curPos += 10.0f; break;
		default: break;
	}

	Text& t = *(new Text( text ));
	credits.push_back( &t );
	t.SetPosition( App.GetWidth() / 2.0f - (t.GetWidth() / 2.0f), curPos );
}



// This makes sure the scene is added to the engine!
SceneCredits* credits = new SceneCredits();
