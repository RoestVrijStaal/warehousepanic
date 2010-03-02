#include "SceneMenu.h"

#include "WCEngine/EventManager.h"
#include "WCEngine/ResourceManager.h"

#include <sstream>


// This is the important part. You need to
SceneMenu::SceneMenu() : Scene( "menu" )
{
	App.AddScene( this );
}

SceneMenu::~SceneMenu()
{
}

void SceneMenu::Initialize()
{
	isKeyDown = true;
	selected = 0;
	isLeavingMenu = false;
	items.push_back( "Play" );
	items.push_back( "Highscore" );
	items.push_back( "Credits" );
	items.push_back( "Quit" );

	soldier1.SetImage( ResMgr.GetImage( "green soldier" ) );
	soldier2.SetImage( ResMgr.GetImage( "red soldier" ) );
	soldier1.SetPosition( 30, 140 );
	soldier2.SetPosition( 140, 130 );
	soldier1.FlipX(true);

	ResMgr.GetMusic( "game over" ).Play();
}

void SceneMenu::Terminate()
{
	items.clear();
	ResMgr.GetMusic( "game over" ).Stop();
}

void SceneMenu::Step()
{
	DoKeyboard();
}

void SceneMenu::Draw()
{
	window->Clear( sf::Color::Black );

	window->Draw( soldier1 );
	window->Draw( soldier2 );

	// Title
	sf::String title( "Warehouse Panic", sf::Font::GetDefaultFont(), TITLE_FONT_SIZE );
	title.SetStyle( sf::String::Bold );
	sf::FloatRect size = title.GetRect();
	title.SetCenter( (size.Right - size.Left) / 2, (size.Bottom - size.Top) / 2 );
	title.SetPosition( 160, 30 );
	title.SetRotation( 6.0f );
	title.SetColor( sf::Color( 255, 255, 255 ) );
	window->Draw( title );

	for ( size_t i = 0; i < items.size(); ++i )
	{
		sf::String text( items[i], sf::Font::GetDefaultFont(), MENU_FONT_SIZE );
		text.SetStyle( sf::String::Bold );
		text.SetPosition( MENU_LEFT, MENU_TOP + MENU_SPACING * i );
		if ( (int)i == selected )
			text.SetColor( sf::Color::Yellow );
		else
			text.SetColor( sf::Color::White );
		window->Draw( text );
	}
}

void SceneMenu::DoKeyboard()
{
	if ( isLeavingMenu )
		return;

	bool up, down, enter;
	up = window->GetInput().IsKeyDown( sf::Key::Up );
	down = window->GetInput().IsKeyDown( sf::Key::Down );
	enter = window->GetInput().IsKeyDown( sf::Key::Return ) or window->GetInput().IsKeyDown( sf::Key::Space );

	if ( up and not isKeyDown )
	{
		isKeyDown = true;
		--selected;
		if ( selected < 0 )
			selected = 0;
	}
	else if ( down and not isKeyDown )
	{
		isKeyDown = true;
		++selected;
		if ( selected >= (int)items.size() )
			selected = (int)items.size() - 1;
	}
	else if ( enter and not isKeyDown )
	{
		switch ( selected )
		{
			case 0:
				{
				EventMgr.PushEvent( ENGINE, GameEvent::ChangeSceneEvent( "game" ) );
				isLeavingMenu = true;
				}
				break;

			case 1:
				EventMgr.PushEvent( ENGINE, GameEvent::ChangeSceneEvent( "highscore" ) );
				isLeavingMenu = true;
				break;

			case 2:
				EventMgr.PushEvent( ENGINE, GameEvent::ChangeSceneEvent( "credits" ) );
				isLeavingMenu = true;
				break;

			case 3:
				EventMgr.PushEvent( ENGINE, GameEvent::QuitEvent() );
				isLeavingMenu = true;
				break;

			default:
				break;
		}
	}
	else if ( not up and not down and not enter )
	{
		isKeyDown = false;
	}
}

SceneMenu* menu = new SceneMenu();
