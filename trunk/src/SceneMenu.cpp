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
	selected = -1;
	isMouseDown = true;
	items.push_back( "Play" );
	items.push_back( "Highscore" );
	items.push_back( "Credits" );
	items.push_back( "Help" );
	items.push_back( "Quit" );

	background.SetImage( ResMgr.GetImage( "loading" ) );

	//ResMgr.GetMusic( "game over" ).Play();
}

void SceneMenu::Terminate()
{
	items.clear();
	//ResMgr.GetMusic( "game over" ).Stop();
}

void SceneMenu::Step()
{
	bool curMouseDown = App.GetWindow().GetInput().IsMouseButtonDown( sf::Mouse::Left );
	sf::Vector2f mousepos( App.GetWindow().GetInput().GetMouseX(), App.GetWindow().GetInput().GetMouseY() );

	// Mouse down event
	if ( curMouseDown and !isMouseDown )
	{
		if ( mousepos.x >= MENU_LEFT and mousepos.y >= MENU_TOP )
		{
			selected = (int)(( mousepos.y - MENU_TOP ) / MENU_SPACING);
			if ( selected >= items.size() )
				selected = -1;
		}
		else
		{
			selected = -1;
		}
	}

	// Mouse drag event
	if ( curMouseDown and isMouseDown )
	{
		if ( mousepos.x < MENU_LEFT or mousepos.y < MENU_TOP or (int)(( mousepos.y - MENU_TOP ) / MENU_SPACING) != selected )
		{
			selected = -1;
		}
	}

	// Mouse release event (on button)
	if ( !curMouseDown and isMouseDown and selected > -1 )
	{
		switch ( selected )
		{
			case 0:
				EventMgr.PushEvent( ENGINE, GameEvent::ChangeSceneEvent( "game" ) );
				break;

			case 1:
				EventMgr.PushEvent( ENGINE, GameEvent::ChangeSceneEvent( "highscore" ) );
				break;

			case 2:
				EventMgr.PushEvent( ENGINE, GameEvent::ChangeSceneEvent( "credits" ) );
				break;

			case 3:
				EventMgr.PushEvent( ENGINE, GameEvent::ChangeSceneEvent( "game" ) ); // TODO: Load tutorial level here
				break;

			case 4:
				EventMgr.PushEvent( ENGINE, GameEvent::QuitEvent() );
				break;

			default:
				break;
		}
	}
	isMouseDown = curMouseDown;
}

void SceneMenu::Draw()
{
	App.GetWindow().Draw( background );

	// Title
	sf::String title( "Warehouse Panic", sf::Font::GetDefaultFont(), TITLE_FONT_SIZE );
	title.SetStyle( sf::String::Bold );
	sf::FloatRect size = title.GetRect();
	title.SetCenter( (size.Right - size.Left) / 2, (size.Bottom - size.Top) / 2 );
	title.SetPosition( 160, 30 );
	title.SetRotation( 6.0f );
	title.SetColor( sf::Color::Black );
	App.GetWindow().Draw( title );

	for ( size_t i = 0; i < items.size(); ++i )
	{
		sf::String text( items[i], sf::Font::GetDefaultFont(), MENU_FONT_SIZE );
		text.SetStyle( sf::String::Bold );
		text.SetPosition( MENU_LEFT, MENU_TOP + MENU_SPACING * i );
		text.SetColor( sf::Color::Black );
		App.GetWindow().Draw( text );
	}
}



SceneMenu* menu = new SceneMenu();
