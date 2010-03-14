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

	// Backgrounds
	images["splash"].LoadFromFile( "media/bg_splash.png" );
	images["title"].LoadFromFile( "media/bg_title.png" );

	// Game graphics
	images["conveyor 02"].LoadFromFile( "media/conveyor_dir_02.png" );
	images["conveyor 13"].LoadFromFile( "media/conveyor_dir_13.png" );
	images["conveyor 02 con 1"].LoadFromFile( "media/conveyor_dir_02_con_1.png" );
	images["conveyor 02 con 3"].LoadFromFile( "media/conveyor_dir_02_con_3.png" );
	images["conveyor 13 con 0"].LoadFromFile( "media/conveyor_dir_13_con_0.png" );
	images["conveyor 13 con 2"].LoadFromFile( "media/conveyor_dir_13_con_2.png" );
	images["conveyor 02 cross"].LoadFromFile( "media/conveyor_dir_02_cross.png" );
	images["conveyor 13 cross"].LoadFromFile( "media/conveyor_dir_13_cross.png" );
	images["conveyor 0 turn"].LoadFromFile( "media/conveyor_dir_0_turn.png" );
	images["conveyor 1 turn"].LoadFromFile( "media/conveyor_dir_1_turn.png" );
	images["conveyor 2 turn"].LoadFromFile( "media/conveyor_dir_2_turn.png" );
	images["conveyor 3 turn"].LoadFromFile( "media/conveyor_dir_3_turn.png" );

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

	images["truck 0"].LoadFromFile( "media/truck_dir0.png" );
	images["truck 1"].LoadFromFile( "media/truck_dir1.png" );

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

	// Sound buffers
	sounds["switch"].LoadFromFile( "media/snd_button-25.wav" );
	sounds["click"].LoadFromFile( "media/snd_button-30.wav" );

	// TODO: Free memory again
	music["new highscore"] = new sf::Music();
	music["new highscore"]->OpenFromFile( "media/music_Ring Of Fire Midi-15375-Free-Loops.com.wav" );
	music["new highscore"]->SetLoop( true );
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
