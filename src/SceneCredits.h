#ifndef SCENECREDITS_H
#define SCENECREDITS_H

#include "WCEngine/Scene.h"

#include "Text.h"


class SceneCredits : public Scene
{
	public:
		SceneCredits();
		virtual ~SceneCredits();

		virtual void Initialize();
		virtual void Terminate();
		virtual void Step();
		virtual void Draw();

		//Just makes this easier (for me :P)
		Text makeString(std::string text, float hlevel, float &yToSet);

	protected:
		bool isMouseDown;
		float curY;

	private:
};

#endif // SCENECREDITS_H
