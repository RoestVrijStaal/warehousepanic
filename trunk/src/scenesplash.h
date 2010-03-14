#ifndef SCENESPLASH_H
#define SCENESPLASH_H

#include "WCEngine/Application.h"
#include "WCEngine/EventManager.h"
#include "WCEngine/ResourceManager.h"
#include "WCEngine/Scene.h"

#define MIN_SPLASH_TIME 120



class SceneSplash : public Scene
{
	public:
		SceneSplash();
		virtual ~SceneSplash();

		void Initialize();
		void Terminate();
		void Step();
		void Draw();

	protected:
		int time;
		sf::Sprite background;

	private:
};

#endif // SCENESPLASH_H
