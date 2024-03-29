#ifndef SCENEHOWTOPLAY_H
#define SCENEHOWTOPLAY_H

#include "WCEngine/GDN.h"

//Includes
#include <vector>


class SceneHowToPlay : public gdn::Scene
{
	public:
		SceneHowToPlay();
		virtual ~SceneHowToPlay();

		void Initialize();
		void Terminate();

		void Step();
		void Draw();

	protected:
		// Misc.
		std::vector<gdn::Sprite> screens;
		std::vector<gdn::Sprite>::iterator cur; // Currently shown screen
		gdn::Sound sndClick;
		bool isMouseDown;
		int timer;

	private:
};

#endif // SCENEHOWTOPLAY_H
