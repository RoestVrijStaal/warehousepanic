#ifndef SCENEHIGHSCORE_H
#define SCENEHIGHSCORE_H

#include "WCEngine/GDN.h"
#include "Keyboard.h"
#include "Score.h"
#include "Text.h"

#include <string>
#include <list>
#include <vector>


class SceneHighscore : public gdn::Scene
{
	public:
		SceneHighscore();
		virtual ~SceneHighscore();

		void Initialize();
		void Terminate();

		void Step();
		void Draw();

	protected:
		void InsertScore( Score* score );
		bool isMouseDown;
		Keyboard* keyboard;
		Score* newScore;
		Text* newTextName; // Pointer to the text for which the newly entered name should be put
		std::list< Score* > scores;
		gdn::Sound sndClick;
		Text highscore_title;
		std::vector< Text* > highscores;

	private:
};

#endif // SCENEHIGHSCORE_H
