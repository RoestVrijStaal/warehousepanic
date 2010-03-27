#ifndef SCENESPLASH_H
#define SCENESPLASH_H

#include "WCEngine/GDN.h"



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

	private:
};

#endif // SCENESPLASH_H
