#include "SceneHowToPlay.h"

#include "WCEngine/EventManager.h"
#include "WCEngine/ResourceManager.h"
#include "WCEngine/Application.h"

using namespace std;



// This is the important part. You need to give this scene a name. I call this one game
SceneHowToPlay::SceneHowToPlay() : Scene( "howtoplay" )
{
}

SceneHowToPlay::~SceneHowToPlay()
{
}

// Not because of this function
void SceneHowToPlay::Initialize()
{
	// Screens
	screens.push_back( sf::Sprite( ResMgr.GetImage( "tutorial 1" ) ) );
	screens.push_back( sf::Sprite( ResMgr.GetImage( "tutorial 2" ) ) );
	screens.push_back( sf::Sprite( ResMgr.GetImage( "tutorial 3" ) ) );
	screens.push_back( sf::Sprite( ResMgr.GetImage( "tutorial 4" ) ) );
	cur = screens.begin();

	// Sounds
	sndClick = sf::Sound( ResMgr.GetSound( "click" ) );

	//Other stuff
	isMouseDown = true;
}

void SceneHowToPlay::Terminate()
{
	screens.clear();
}

void SceneHowToPlay::Step()
{
	if ( timer > 0 )
		--timer;

	//Events
	sf::Vector2f mousepos( App.GetWindow().GetInput().GetMouseX(), App.GetWindow().GetInput().GetMouseY()) ;
	bool newMouseButton = App.GetWindow().GetInput().IsMouseButtonDown( sf::Mouse::Left );

	// Handle mouse-down event
	if ( newMouseButton and isMouseDown == false and cur != screens.end() )
	{
		sndClick.Play();
		++cur;

		if ( cur == screens.end() )
		{
			timer = 25;
		}
	}

	// End scene?
	if ( cur == screens.end() and timer == 0 )
		EventMgr.PushEvent( ENGINE, GameEvent::ChangeSceneEvent( "menu" ) );

	isMouseDown = newMouseButton;
}

void SceneHowToPlay::Draw()
{
	if ( cur == screens.end() )
		App.GetWindow().Clear( sf::Color(0, 0, 0) );
	else
		App.GetWindow().Draw( *cur );
}



// This makes sure the scene is added to the engine!
SceneHowToPlay* howToPlay = new SceneHowToPlay();
