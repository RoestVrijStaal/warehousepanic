#ifndef SCENEGAME_H
#define SCENEGAME_H

#include "WCEngine/Scene.h"

//Includes
#include <sstream>
#include <vector>
#include <string>

#include "conveyor.h"
#include "crate.h"
#include "truck.h"
#include "gate.h"

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
        //Misc.
		unsigned int points;
		bool paused;
        int csel;

		//Game Object Contaiers
		std::vector<conveyor> conveyors;
        std::vector<crate> crates;
        std::vector<sf::Sprite> incinerators;
        std::vector<gate> gates;
        std::vector<truck> trucks;

        //Resources
        sf::Image img_crate_red;
        sf::Image img_crate_orange;
        sf::Image img_crate_yellow;
        sf::Image img_crate_green;
        sf::Image img_crate_blue;
        sf::Image img_crate_purple;

        sf::Image img_conveyor_vert;
        sf::Image img_conveyor_hor;
        sf::Image img_incinerator;
        sf::Image img_truck_right;

        sf::Image img_arrow_vert_left;
        sf::Image img_arrow_vert_right;
        sf::Image img_arrow_vertr_left;
        sf::Image img_arrow_vertr_right;
        sf::Image img_arrow_hor_left;
        sf::Image img_arrow_hor_right;

        sf::Image img_gate_red_right;
        sf::Image img_gate_orange_right;
        sf::Image img_gate_yellow_right;
        sf::Image img_gate_green_right;
        sf::Image img_gate_blue_right;
        sf::Image img_gate_purple_right;

        sf::Font fnt_arial_lrg;
        sf::Font fnt_arial_sml;

        //Other Game Stuff
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

	private:
};

#endif // SCENEGAME_H
