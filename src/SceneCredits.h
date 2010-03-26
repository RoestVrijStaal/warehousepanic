#ifndef SCENECREDITS_H
#define SCENECREDITS_H

#include "WCEngine/GDN.h"

#include "Text.h"
#include <vector>
#include <string>

class SceneCredits : public gdn::Scene
{
	public:
		SceneCredits();
		virtual ~SceneCredits();

		virtual void Initialize();
		virtual void Terminate();
		virtual void Step();
		virtual void Draw();

	protected:
		void AddText( std::string text, Text::Size size );
		std::vector< Text* > credits;
		bool isMouseDown;
		float curOffset;

	private:
};

#endif // SCENECREDITS_H
