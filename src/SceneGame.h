#ifndef SCENEGAME_H
#define SCENEGAME_H

#include "WCEngine/Scene.h"

// Some include files here

// Define some settings here



class SceneGame : public Scene
{
	public:
		SceneGame();
		virtual ~SceneGame();

		void Initialize();
		void Terminate();

		void Step();
		void Draw();

	protected:
		// Some game data here

	private:
};

#endif // SCENEGAME_H
