#ifndef SCENEMENU_H
#define SCENEMENU_H

#include <SFML/Audio.hpp>
#include "WCEngine/GDN.h"

#include <string>
#include <vector>



// Settings
#define MENU_LEFT (228.0f)
#define MENU_TOP (108.0f)
#define MENU_SPACING (28.0f)



class SceneMenu : public gdn::Scene
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
		gdn::Sprite background;
		sf::Sound sndClick;

	private:
};

#endif // SCENEMENU_H
