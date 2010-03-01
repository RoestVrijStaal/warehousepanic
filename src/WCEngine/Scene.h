#ifndef SCENE_H
#define SCENE_H

#include "Application.h"
#include <SFML/Graphics.hpp>
#include <string>

class Scene
{
	public:
		Scene( std::string name );
		virtual ~Scene();
		void SetRenderWindow( sf::RenderWindow& window );
		std::string GetName();

		virtual void Initialize() = 0; // Set up scene, create objects etc.
		virtual void Terminate() = 0; // Clean up, deleting objects and freeing memory
		virtual void Step() = 0;
		virtual void Draw() = 0;

	protected:
		sf::RenderWindow* window;
		std::string name;

	private:
};

#endif // SCENE_H
