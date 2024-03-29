#ifndef APP_H
#define APP_H

#include "RenderWindow.h"

#include <string>
#include <map>
#include <list>



// Settings
#define DEFAULT_PHYSICS_FPS (100.0f)




#define App (*(gdn::Application::GetInstance()))

namespace gdn
{
	// Forward decl.
	class Scene;
	class Timer;
	class Animation;

	class Application
	{
	public:
		static Application* GetInstance();

		bool Initialize( int width, int height, int bpp, std::string title ); // Open screen
		void SetPhysicsFPS( float fps );
		void Run(); // Start engine

		void AddScene( Scene* scene );
		gdn::RenderWindow& GetWindow();

		void AddAnimation( Animation* anim );
		void RemoveAnimation( Animation* anim );

		int GetWidth();
		int GetHeight();
		int GetBPP();
		float GetFPS();

	protected:
		Application();
		virtual ~Application();

		void ProcessSystemEvents();
		void ProcessGameEvents(); // Home-made events
		void SetScene( std::string name );
		void Step();
		void Draw();

		gdn::RenderWindow window;
		bool isRunning;
		gdn::Timer* timer;
		float physicsFps;
		int width;
		int height;
		int bpp;
		int volume;
		std::string title;

		// Current scene (game, menu, highscore etc.)
		Scene* curScene;
		std::map< std::string, Scene* > scenes;

		std::list< Animation* > animations;

	private:
		static Application* instance;
	};
} // namespace

#endif // APP_H
