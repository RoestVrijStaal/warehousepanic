#include "ResourceManager.h"


ResourceManager* ResourceManager::instance = NULL;

ResourceManager* ResourceManager::GetInstance()
{
	if ( instance == NULL )
	{
		instance = new ResourceManager();
	}
	return instance;
}

ResourceManager::ResourceManager()
{
	Initialize();
}

ResourceManager::~ResourceManager()
{
	if ( instance != NULL )
	{
		delete instance;
		instance = NULL;
	}
}

void ResourceManager::Initialize()
{
	// Empty objects returned when requested object not found
	images["dummy"] = sf::Image();
	sounds["dummy"] = sf::SoundBuffer();

	// Images
	images["loading"].LoadFromFile( "media/loading.png" );

	// Game graphics
	images["conveyor 0"].LoadFromFile( "media/conveyor_dir1.png" );
	images["conveyor 0 turn left"].LoadFromFile( "media/conveyor_dir1_turn_left.png" );
	images["conveyor 0 turn right"].LoadFromFile( "media/conveyor_dir1_turn_right.png" );
	images["conveyor 1"].LoadFromFile( "media/conveyor_dir2.png" );
	images["conveyor 1 turn left"].LoadFromFile( "media/conveyor_dir2_turn_left.png" );
	images["conveyor 1 turn right"].LoadFromFile( "media/conveyor_dir2_turn_right.png" );
	images["conveyor 2"].LoadFromFile( "media/conveyor_dir3.png" );
	images["conveyor 2 turn left"].LoadFromFile( "media/conveyor_dir3_turn_left.png" );
	images["conveyor 2 turn right"].LoadFromFile( "media/conveyor_dir3_turn_right.png" );
	images["conveyor 3"].LoadFromFile( "media/conveyor_dir4.png" );
	images["conveyor 3 turn left"].LoadFromFile( "media/conveyor_dir4_turn_left.png" );
	images["conveyor 3 turn right"].LoadFromFile( "media/conveyor_dir4_turn_right.png" );

	images["crate blue"].LoadFromFile( "media/crate-blue.png" );
	images["crate green"].LoadFromFile( "media/crate-green.png" );
	images["crate orange"].LoadFromFile( "media/crate-orange.png" );
	images["crate purple"].LoadFromFile( "media/crate-purple.png" );
	images["crate red"].LoadFromFile( "media/crate-red.png" );
	images["crate yellow"].LoadFromFile( "media/crate-yellow.png" );

	images["gate 0 blue"].LoadFromFile( "media/gate-blue-right-fg.png" );
	images["gate bg 0 blue"].LoadFromFile( "media/gate-blue-right-bg.png" );
	images["gate 1 blue"].LoadFromFile( "media/gate-blue-left-fg.png" );
	images["gate bg 1 blue"].LoadFromFile( "media/gate-blue-left-bg.png" );

	images["gate 0 green"].LoadFromFile( "media/gate-green-right-fg.png" );
	images["gate bg 0 green"].LoadFromFile( "media/gate-green-right-bg.png" );
	images["gate 1 green"].LoadFromFile( "media/gate-green-left-fg.png" );
	images["gate bg 1 green"].LoadFromFile( "media/gate-green-left-bg.png" );

	images["gate 0 orange"].LoadFromFile( "media/gate-orange-right-fg.png" );
	images["gate bg 0 orange"].LoadFromFile( "media/gate-orange-right-bg.png" );
	images["gate 1 orange"].LoadFromFile( "media/gate-orange-left-fg.png" );
	images["gate bg 1 orange"].LoadFromFile( "media/gate-orange-left-bg.png" );

	images["gate 0 purple"].LoadFromFile( "media/gate-purple-right-fg.png" );
	images["gate bg 0 purple"].LoadFromFile( "media/gate-purple-right-bg.png" );
	images["gate 1 purple"].LoadFromFile( "media/gate-purple-left-fg.png" );
	images["gate bg 1 purple"].LoadFromFile( "media/gate-purple-left-bg.png" );

	images["gate 0 red"].LoadFromFile( "media/gate-red-right-fg.png" );
	images["gate bg 0 red"].LoadFromFile( "media/gate-red-right-bg.png" );
	images["gate 1 red"].LoadFromFile( "media/gate-red-left-fg.png" );
	images["gate bg 1 red"].LoadFromFile( "media/gate-red-left-bg.png" );

	images["gate 0 yellow"].LoadFromFile( "media/gate-yellow-right-fg.png" );
	images["gate bg 0 yellow"].LoadFromFile( "media/gate-yellow-right-bg.png" );
	images["gate 1 yellow"].LoadFromFile( "media/gate-yellow-left-fg.png" );
	images["gate bg 1 yellow"].LoadFromFile( "media/gate-yellow-left-bg.png" );

	images["button pause"].LoadFromFile( "media/button_pause.png" );
	images["button pause active"].LoadFromFile( "media/button_pause_on.png" );
	images["button quit"].LoadFromFile( "media/button_quit.png" );
	images["button quit active"].LoadFromFile( "media/button_quit_on.png" );

	images["text paused"].LoadFromFile( "media/text_paused.png" );
//	images["text game over"].LoadFromFile( "media/text_game_over.png" );
//	images["text level complete"].LoadFromFile( "media/text_level_complete.png" );

	images["keyboard"].LoadFromFile( "media/keyboard.png" );

	// Font
	images["A small"].LoadFromFile( "media/font_a_small.png" );
	images["B small"].LoadFromFile( "media/font_b_small.png" );
	images["C small"].LoadFromFile( "media/font_c_small.png" );
	images["D small"].LoadFromFile( "media/font_d_small.png" );
	images["I small"].LoadFromFile( "media/font_i_small.png" );


/*	images["level background"].LoadFromFile( "media/levelbg.png" );
	images[""].LoadFromFile( "media/text_.png" );
	images[""].LoadFromFile( "media/.png" );
	images[""].LoadFromFile( "media/.png" );
	images[""].LoadFromFile( "media/.png" );
	images[""].LoadFromFile( "media/.png" );
	images[""].LoadFromFile( "media/.png" );
	images[""].LoadFromFile( "media/.png" );*/

	// Sound buffers
	sounds["switch"].LoadFromFile( "media/snd_button-25.wav" );

	// TODO: Free memory again
	music["game over"] = new sf::Music();
	music["game over"]->OpenFromFile( "media/music_Sweet RnB Beat-23820-Free-Loops.com.wav" );
	music["game over"]->SetLoop( true );
	music["menu"] = new sf::Music();
	music["menu"]->OpenFromFile( "media/music_Free Hip Hop 3-9480-Free-Loops.com.wav" );
	music["menu"]->SetLoop( true );
}

sf::Image& ResourceManager::GetImage( std::string name )
{
	std::map< std::string, sf::Image >::iterator result = images.find( name );
	if ( result == images.end() )
	{
		return images["dummy"];
	}
	else
	{
		return result->second;
	}
}

sf::SoundBuffer& ResourceManager::GetSound( std::string name )
{
	std::map< std::string, sf::SoundBuffer >::iterator result = sounds.find( name );
	if ( result == sounds.end() )
	{
		return sounds["dummy"];
	}
	else
	{
		return result->second;
	}
}

sf::Music& ResourceManager::GetMusic( std::string name )
{
	std::map< std::string, sf::Music* >::iterator result = music.find( name );
	if ( result == music.end() )
	{
		return *music["dummy"];
	}
	else
	{
		return *result->second;
	}
}
