#include "SceneCredits.h"
#include "WCEngine/Application.h"
#include "WCEngine/EventManager.h"
#include "WCEngine/ResourceManager.h"



SceneCredits::SceneCredits() : Scene( "credits" )
{
}

SceneCredits::~SceneCredits()
{
}

void SceneCredits::Initialize()
{
	isMouseDown = true;
}

void SceneCredits::Terminate()
{
}

void SceneCredits::Step()
{
	bool curMouseDown = App.GetWindow().GetInput().IsMouseButtonDown( sf::Mouse::Left );
	if ( curMouseDown and !isMouseDown ) // Mouse down event
	{
		EventMgr.PushEvent( ENGINE, GameEvent::QuitEvent() );
	}
	isMouseDown = curMouseDown;
}

void SceneCredits::Draw()
{
	App.GetWindow().Clear( sf::Color( 0, 0, 0 ) );
	sf::String str( "credits", sf::Font::GetDefaultFont(), 12 );
	str.SetPosition( 10, 60 );
	App.GetWindow().Draw( str );
}



// This makes sure the scene is added to the engine!
SceneCredits* credits = new SceneCredits();
