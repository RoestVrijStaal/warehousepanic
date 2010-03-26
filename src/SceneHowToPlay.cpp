#include "SceneHowToPlay.h"



// This is the important part. You need to give this scene a name. I call this one game
SceneHowToPlay::SceneHowToPlay() : Scene( "howtoplay" )
{
}

SceneHowToPlay::~SceneHowToPlay()
{
}

void SceneHowToPlay::Initialize()
{
	// Screens
	screens.push_back( gdn::Sprite( ResMgr.GetImage( "tutorial 1" ) ) );
	screens.push_back( gdn::Sprite( ResMgr.GetImage( "tutorial 2" ) ) );
	screens.push_back( gdn::Sprite( ResMgr.GetImage( "tutorial 3" ) ) );
	screens.push_back( gdn::Sprite( ResMgr.GetImage( "tutorial 4" ) ) );
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
	gdn::Vector2f mousepos( App.GetWindow().GetMouseX(), App.GetWindow().GetMouseY() );
	bool newMouseButton = App.GetWindow().IsMouseButtonDown();

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
		EventMgr.PushEvent( gdn::ENGINE, gdn::GameEvent::ChangeSceneEvent( "menu" ) );

	isMouseDown = newMouseButton;
}

void SceneHowToPlay::Draw()
{
	if ( cur == screens.end() )
		App.GetWindow().Clear( 0, 0, 0 );
	else
		App.GetWindow().Draw( *cur );
}



// This makes sure the scene is added to the engine!
SceneHowToPlay* howToPlay = new SceneHowToPlay();
