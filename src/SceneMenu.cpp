#include "SceneMenu.h"

#include <sstream>


// This is the important part. You need to add the name of this scene
SceneMenu::SceneMenu() : Scene( "menu" )
{
}

SceneMenu::~SceneMenu()
{
}

void SceneMenu::Initialize()
{
	selected = -1;
	isMouseDown = true;
	items.push_back( "Play" );
	items.push_back( "How to Play" );
	items.push_back( "Highscore" );
	items.push_back( "Quit" );

	background = gdn::Sprite( ResMgr.GetImage( "title" ) );

	if ( !ResMgr.GetMusic( "menu" ).IsPlaying() )
	{
		ResMgr.GetMusic( "menu" ).Play();
	}
	sndClick = gdn::Sound( ResMgr.GetSound( "click" ) );
}

void SceneMenu::Terminate()
{
	background = gdn::Sprite();
	items.clear();
}

void SceneMenu::Step()
{
	bool curMouseDown = App.GetWindow().IsMouseButtonDown();
	gdn::Vector2f mousepos( App.GetWindow().GetMouseX(), App.GetWindow().GetMouseY() );

	// Mouse down event
	if ( curMouseDown and !isMouseDown )
	{
		if ( mousepos.x >= MENU_LEFT and mousepos.x <= MENU_LEFT + MENU_WIDTH and mousepos.y >= MENU_TOP )
		{
			selected = (int)(( mousepos.y - MENU_TOP ) / MENU_SPACING);
			if ( selected >= (int)items.size() )
				selected = -1;
			else
				sndClick.Play();
		}
		else
		{
			selected = -1;
		}
	}

	// Mouse drag event
	if ( curMouseDown and isMouseDown )
	{
		if ( mousepos.x < MENU_LEFT or mousepos.x > MENU_LEFT + MENU_WIDTH or mousepos.y < MENU_TOP or (int)(( mousepos.y - MENU_TOP ) / MENU_SPACING) != selected )
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
				EventMgr.PushEvent( gdn::ENGINE, gdn::GameEvent::ChangeSceneEvent( "game" ) );
				EventMgr.PushEvent( gdn::GAME, gdn::GameEvent::ChangeLevelEvent( 1 ) );
				EventMgr.PushEvent( gdn::GAME, gdn::GameEvent::ChangeScoreEvent( 0 ) );
				ResMgr.GetMusic( "menu" ).Stop();
				break;

			case 1:
				EventMgr.PushEvent( gdn::ENGINE, gdn::GameEvent::ChangeSceneEvent( "howtoplay" ) );
				break;

			case 2:
				EventMgr.PushEvent( gdn::ENGINE, gdn::GameEvent::ChangeSceneEvent( "highscore" ) );
				break;

			case 3:
				EventMgr.PushEvent( gdn::ENGINE, gdn::GameEvent::ChangeSceneEvent( "credits" ) );
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
	//for ( size_t i = 0; i < items.size(); ++i )
	//{
		//sf::String text( items[i], sf::Font::GetDefaultFont(), MENU_FONT_SIZE );
		//text.SetStyle( sf::String::Bold );
		//text.SetPosition( MENU_LEFT, MENU_TOP + MENU_SPACING * i );
		//text.SetColor( sf::Color::Red );
		//App.GetWindow().Draw( text );
	//}
}



SceneMenu* menu = new SceneMenu();
