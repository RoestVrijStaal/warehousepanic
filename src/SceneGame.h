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
		std::list<Object*> toDelete; // List of objects that we are responsible for deleting
		int points;
		int csel;
		bool isPaused;
		Level level;

		// Other Game Stuff
		sf::String str_paused_msg1;
		sf::String str_paused_msg2;
		sf::String str_paused_msg3;
		sf::String str_score;

		sf::Shape pbutton1;
		sf::Shape pbutton2;

		//Keys and such
		bool isMouseDown;
		bool isEnterDown;
		bool isUpDown;
		bool isDownDown;

		// Helper functions
		sf::Vector2f TransformScreenToMap( sf::Vector2f& pos );
		sf::Vector2f TransformMapToScreen( sf::Vector2f& pos );
		float GetDistanceSQ( sf::Vector2f pos1, sf::Vector2f pos2 );
		bool DoCrate( Crate& crate );
		bool DoTruck( Truck& truck );

	private:
};

#endif // SCENEGAME_H
