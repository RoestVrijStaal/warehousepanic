#ifndef SCENEMENU_H
#define SCENEMENU_H

#include "WCEngine/GDN.h"

#include <string>
#include <vector>



// Settings
#define MENU_LEFT (18.0f)
#define MENU_WIDTH (86.0f)
#define MENU_TOP (80.0f)
#define MENU_SPACING (36.0f)



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
		gdn::Sound sndClick;

	private:
};

#endif // SCENEMENU_H
