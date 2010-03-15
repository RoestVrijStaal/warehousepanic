#ifndef SCENEHOWTOPLAY_H
#define SCENEHOWTOPLAY_H

#include "WCEngine/Scene.h"
#include <SFML/Audio.hpp>

//Includes
#include <vector>



// Define some settings here



class SceneHowToPlay : public Scene
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
		std::vector<sf::Sprite> screens;
		std::vector<sf::Sprite>::iterator cur; // Currently shown screen
		sf::Sound sndClick;
		bool isMouseDown;
		int timer;

	private:
};

#endif // SCENEHOWTOPLAY_H
