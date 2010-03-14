#ifndef SCENEMENU_H
#define SCENEMENU_H

#include <SFML/Audio.hpp>
#include "WCEngine/Scene.h"

#include <string>
#include <vector>



// Settings
#define MENU_LEFT (230.0f)
#define MENU_TOP (115.0f)
#define MENU_SPACING (33.0f)



class SceneMenu : public Scene
{
	public:
		SceneMenu();
		virtual ~SceneMenu();

		void Initialize();
		void Terminate();

		void Step();
		void Draw();

	protected:
		int selected;
		bool isMouseDown;
		std::vector<std::string> items;
		sf::Sprite background;
		sf::Sound sndClick;

	private:
};

#endif // SCENEMENU_H
