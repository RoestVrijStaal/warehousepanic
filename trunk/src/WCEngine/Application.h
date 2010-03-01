#ifndef APP_H
#define APP_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>



// Settings
#define DEFAULT_PHYSICS_FPS (100.0f)





#define App (*(Application::GetInstance()))

// Forward decl.
class Scene;

class Application
{
public:
	static Application* GetInstance();

	bool Initialize(); // Open screen
	void SetPhysicsFPS( float fps );
	void Run(); // Start engine

	void AddScene( Scene* scene );

protected:
	Application();
	virtual ~Application();

	void ProcessSystemEvents(); // SFML events
	void ProcessGameEvents(); // Home-made events
	void SetScene( std::string name );
	void Step();
	void Draw();

	sf::RenderWindow window;
	bool isRunning;
	sf::Clock timer;
	float physicsFps;

	// Current scene (game, menu, highscore etc.)
	Scene* curScene;
	std::map< std::string, Scene* > scenes;

private:
	static Application* instance;
};

#endif // APP_H
