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
	images["red soldier"].LoadFromFile( "media/red_soldier.png" );
	images["green soldier"].LoadFromFile( "media/green_soldier.png" );

	// Sound buffers
	//sounds["something"].LoadFromFile( "media/somesoundeffect.wav" );

	// TODO: Free memory again
	music["game over"] = new sf::Music( 96000 );
	music["game over"]->OpenFromFile( "media/Sweet RnB Beat-23820-Free-Loops.com.wav" );
	music["game over"]->SetLoop( true );
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
