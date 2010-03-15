#ifndef SCENEHIGHSCORE_H
#define SCENEHIGHSCORE_H

#include "WCEngine/Scene.h"
#include "Keyboard.h"
#include "Score.h"

#include <SFML/Audio.hpp>
#include <string>
#include <list>



class SceneHighscore : public Scene
{
	public:
		SceneHighscore();
		virtual ~SceneHighscore();

		void Initialize();
		void Terminate();

		void Step();
		void Draw();

	protected:
		bool isMouseDown;
		Keyboard* keyboard;
		int newScore;
		std::string name;
		bool didChange;
		std::list< Score > scores;
		sf::Sound sndClick;

	private:
};

#endif // SCENEHIGHSCORE_H
