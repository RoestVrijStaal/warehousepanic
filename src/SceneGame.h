#ifndef SCENEGAME_H
#define SCENEGAME_H

#include "WCEngine/Scene.h"

//Includes
#include "Level.h"
#include "Object.h"
#include "Crate.h"
#include "Conveyor.h"
#include "Truck.h"
#include "Gate.h"
#include "Text.h"

#include <sstream>
#include <list>
#include <string>



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
		// Misc.
		std::list<Object*> objects;
		std::list<Object*> clickables;
		std::list<Object*> toDelete; // List of objects that we are responsible for deleting
		int points;
		bool isPaused;
		bool isGameOver;
		Level level;
		int timer; // Used for all sorts of stuff, e.g. delay between game being over and scene actually ending

		// Other Game Stuff
		Text str_score;
		Text str_time;

		sf::Sprite pbuttonPause;
		sf::Sprite pbuttonQuit;
		sf::Sprite* popup;

		sf::Sound sndSwitch;
		sf::Sound sndClick;

		//Keys and such
		bool isMouseDown;

		// Helper functions
		sf::Vector2f TransformScreenToMap( sf::Vector2f& pos );
		sf::Vector2f TransformMapToScreen( sf::Vector2f& pos );
		float GetDistanceSQ( sf::Vector2f pos1, sf::Vector2f pos2 );
		Object* FindClickedObject( sf::Vector2f& mappos );
		bool DoCrate( Crate& crate );
		bool DoTruck( Truck& truck );

	private:
};

#endif // SCENEGAME_H
