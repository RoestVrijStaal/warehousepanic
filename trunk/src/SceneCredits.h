#ifndef SCENECREDITS_H
#define SCENECREDITS_H

#include "WCEngine/Scene.h"



class SceneCredits : public Scene
{
	public:
		SceneCredits();
		virtual ~SceneCredits();

		virtual void Initialize();
		virtual void Terminate();
		virtual void Step();
		virtual void Draw();

	protected:
		bool isMouseDown;

	private:
};

#endif // SCENECREDITS_H
