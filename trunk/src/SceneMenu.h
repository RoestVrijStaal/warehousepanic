#ifndef SCENEMENU_H
#define SCENEMENU_H

#include "WCEngine/Scene.h"

#include <string>
#include <vector>



// Settings
#define MENU_LEFT (200.0f)
#define MENU_TOP (100.0f)
#define MENU_SPACING (24.0f)
#define MENU_FONT_SIZE (16.0f)
#define TITLE_FONT_SIZE (40.0f)



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
		void DoKeyboard();

		int selected;
		bool isKeyDown;
		bool isLeavingMenu;
		std::vector<std::string> items;

		// Two characters on the main screen
		sf::Sprite soldier1;
		sf::Sprite soldier2;

	private:
};

#endif // SCENEMENU_H
