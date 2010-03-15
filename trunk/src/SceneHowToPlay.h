#ifndef SCENEHOWTOPLAY_H
#define SCENEHOWTOPLAY_H

#include "WCEngine/Scene.h"

//Includes
#include "Level.h"
#include "Object.h"
#include "Crate.h"
#include "Conveyor.h"
#include "Truck.h"
#include "Gate.h"

#include <sstream>
#include <list>
#include <string>



// Define some settings here



class SceneHowToPlay : public Scene
{
	public:
		SceneHowToPlay();
		virtual ~SceneHowToPlay();

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
		bool takeClicks;
		Level level;
		int timer; // Used for all sorts of stuff, e.g. delay between game being over and scene actually ending
		int step;

		// Other Game Stuff
		sf::String str_score;
		sf::String str_howto;

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

#endif // SCENEHOWTOPLAY_H
