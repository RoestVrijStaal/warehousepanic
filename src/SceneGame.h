#ifndef SCENEGAME_H
#define SCENEGAME_H

#include "WCEngine/GDN.h"

//Includes
#include "Level.h"
#include "Object.h"
#include "Crate.h"
#include "Conveyor.h"
#include "Truck.h"
#include "Gate.h"
#include "Text.h"
#include "Star.h"

#include <list>
#include <vector>
#include <string>



// Define some settings here

// Number of crates allowed to miss per level
#define NUM_CRATES 5



class SceneGame : public gdn::Scene
{
	public:
		SceneGame();
		virtual ~SceneGame();

		void Initialize();
		void Terminate();

		void Step();
		void Draw();

	protected:
		// Misc.
		std::list<Object*> objects;
		std::list<Object*> clickables;
		std::list<Object*> toDelete; // List of objects that we are responsible for deleting
		std::list<Star*> stars;
		int points;
		bool isPaused;
		bool isGameOver;
		bool didWin;
		bool didQuit;
		bool justStopped;
		bool sound;
		Level level;
		int timer; // Used for all sorts of stuff, e.g. delay between game being over and scene actually ending
		int cratesLost;
		int curLevel;

		// Other Game Stuff
		Text str_score;
		//Text str_time;

		gdn::Sprite pbuttonPause;
		gdn::Sprite pbuttonQuit;
		gdn::Sprite* popup;
		gdn::Sprite background;
		gdn::Animation click;

		gdn::Sound sndSwitch;
		gdn::Sound sndClick;
		gdn::Sound sndCrate;
		gdn::Sound sndBack;
		gdn::Sound sndDrive;
		gdn::Sound sndPoint;
		gdn::Sound sndLife;
		gdn::Sound sndWin;
		gdn::Sound sndFail;

		//Keys and such
		bool isMouseDown;

		// Helper functions
		gdn::Vector2f TransformScreenToMap( gdn::Vector2f& pos );
		gdn::Vector2f TransformMapToScreen( gdn::Vector2f& pos );
		float GetDistanceSQ( gdn::Vector2f& pos1, gdn::Vector2f& pos2 );
		Object* FindClickedObject( gdn::Vector2f& mappos );
		bool DoCrate( Crate& crate );
		bool DoTruck( Truck& truck );

	private:
};

#endif // SCENEGAME_H
