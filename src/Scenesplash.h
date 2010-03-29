#ifndef SCENESPLASH_H
#define SCENESPLASH_H

#include "WCEngine/GDN.h"
#include "Text.h"
#include <vector>


#define MIN_SPLASH_TIME (App.GetFPS() * 3)



class SceneSplash : public gdn::Scene
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
		gdn::Sprite background;
		std::vector<Text*> presenters;

	private:
};

#endif // SCENESPLASH_H
