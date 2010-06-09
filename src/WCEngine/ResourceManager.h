#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <map>
#include "Image.h"
#include "SoundBuffer.h"
#include "Music.h"

#define ResMgr (*(gdn::ResourceManager::GetInstance()))

#if defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)
#define RESOURCE_BASE_DIR "Warehouse Panic - Mac Build.app/Contents/Resources/"
#else
#include RESOURCE_BASE_DIR std::string( RESOURCE_BASE_DIR ) + ""
#endif

namespace gdn
{
	class ResourceManager
	{
	public:
		static ResourceManager* GetInstance();

		gdn::Image& GetImage( std::string name );
		gdn::SoundBuffer& GetSound( std::string name );
		gdn::Music& GetMusic( std::string name );

	protected:
		ResourceManager(); // Protected constructor, so noone can create an instance
		~ResourceManager();
		void Initialize();

		std::map< std::string, gdn::Image > images;
		std::map< std::string, gdn::SoundBuffer > sounds;
		std::map< std::string, gdn::Music > music;

	private:
		static ResourceManager* instance;
	};
}

#endif // RESOURCEMANAGER_H
