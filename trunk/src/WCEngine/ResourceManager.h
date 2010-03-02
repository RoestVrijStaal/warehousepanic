#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define ResMgr (*(ResourceManager::GetInstance()))



class ResourceManager
{
public:
	static ResourceManager* GetInstance();

	sf::Image& GetImage( std::string name );
	sf::SoundBuffer& GetSound( std::string name );
	sf::Music& GetMusic( std::string name );

protected:
	ResourceManager(); // Protected constructor, so noone can create an instance
	~ResourceManager();
	void Initialize();

	std::map< std::string, sf::Image > images;
	std::map< std::string, sf::SoundBuffer > sounds;
	std::map< std::string, sf::Music* > music;

private:
	static ResourceManager* instance;
};

#endif // RESOURCEMANAGER_H
