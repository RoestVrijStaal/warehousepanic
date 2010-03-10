#ifndef SCENEHIGHSCORE_H
#define SCENEHIGHSCORE_H

#include "WCEngine/Scene.h"
#include "Keyboard.h"
#include <string>



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

	private:
};

#endif // SCENEHIGHSCORE_H
