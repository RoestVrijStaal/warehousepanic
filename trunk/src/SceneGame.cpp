#include "SceneGame.h"

#include "WCEngine/EventManager.h"
#include "WCEngine/ResourceManager.h"




// This is the important part. You need to give this scene a name. I call this one game
SceneGame::SceneGame() : Scene( "game" )
{
	App.AddScene( this );
}

SceneGame::~SceneGame()
{
}

void SceneGame::Initialize()
{
	// Load level here, set up graphics etc.
}

void SceneGame::Terminate()
{
	// Free any resources reserved in initialize()
}

void SceneGame::Step()
{
	// For now we just go back too the menu if player clicks mouse (or enter or space)
	if ( window->GetInput().IsMouseButtonDown( sf::Mouse::Left ) )
	{
		EventMgr.PushEvent( ENGINE, GameEvent::ChangeSceneEvent( "menu" ) );
	}
}

void SceneGame::Draw()
{
	window->Clear( sf::Color::Black );

	// Draw some text so you see it is working
	sf::String text( "the game (click here)", sf::Font::GetDefaultFont(), 16 );
	text.SetStyle( sf::String::Bold );
	sf::FloatRect size = text.GetRect();
	text.SetCenter( (size.Right - size.Left) / 2, (size.Bottom - size.Top) / 2 );
	text.SetPosition( 160, 120 );
	text.SetRotation( -3.0f );
	text.SetColor( sf::Color( 255, 255, 255 ) );
	window->Draw( text );
}



// This makes sure the scene is added to the engine!
SceneGame* game = new SceneGame();
