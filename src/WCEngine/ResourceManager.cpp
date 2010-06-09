#include "ResourceManager.h"

namespace gdn
{
	ResourceManager* ResourceManager::instance = NULL;

	ResourceManager* ResourceManager::GetInstance()
	{
		if ( instance == NULL )
		{
			instance = new ResourceManager();
		}
		return instance;
	}

	ResourceManager::ResourceManager()
	{
		Initialize();
	}

	ResourceManager::~ResourceManager()
	{
		if ( instance != NULL )
		{
			delete instance;
			instance = NULL;
		}
	}

	void ResourceManager::Initialize()
	{
		// Empty objects returned when requested object not found
		images["dummy"] = gdn::Image();
		sounds["dummy"] = gdn::SoundBuffer();
		music["dummy"] = gdn::Music();

		// Backgrounds
		images["splash"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "bg_splash.png" );
		images["title"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "bg_title.png" );
		images["general"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "bg_general.png" );
		images["level"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "bg_level.png" );
		images["tutorial 1"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "bg_tutorial_1.png" );
		images["tutorial 2"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "bg_tutorial_2.png" );
		images["tutorial 3"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "bg_tutorial_3.png" );
		images["tutorial 4"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "bg_tutorial_4.png" );

		images["click 1"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "click_01.png", true );
		images["click 2"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "click_02.png", true );
		images["click 3"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "click_03.png", true );
		images["click 4"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "click_04.png", true );
		images["click 5"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "click_05.png", true );
		images["click 6"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "click_06.png", true );
		images["click 7"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "click_07.png", true );
		images["click 8"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "click_08.png", true );
		images["click 9"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "click_09.png", true );
		images["click 10"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "click_10.png", true );

		// Game graphics
		images["conveyor 02"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "conveyor_dir_02.png" );
		images["conveyor 13"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "conveyor_dir_13.png" );
		images["conveyor 02 con 1"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "conveyor_dir_02_con_1.png" );
		images["conveyor 02 con 3"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "conveyor_dir_02_con_3.png" );
		images["conveyor 13 con 0"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "conveyor_dir_13_con_0.png" );
		images["conveyor 13 con 2"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "conveyor_dir_13_con_2.png" );
		images["conveyor 02 cross"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "conveyor_dir_02_cross.png" );
		images["conveyor 13 cross"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "conveyor_dir_13_cross.png" );
		images["conveyor 0 turn"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "conveyor_dir_0_turn.png" );
		images["conveyor 1 turn"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "conveyor_dir_1_turn.png" );
		images["conveyor 2 turn"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "conveyor_dir_2_turn.png" );
		images["conveyor 3 turn"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "conveyor_dir_3_turn.png" );
		images["conveyor 0 turn high"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "conveyor_dir_0_turn_high.png" );
		images["conveyor 1 turn high"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "conveyor_dir_1_turn_high.png" );
		images["conveyor 2 turn high"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "conveyor_dir_2_turn_high.png" );
		images["conveyor 3 turn high"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "conveyor_dir_3_turn_high.png" );

		images["crate blue"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "crate-blue.png" );
		images["crate green"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "crate-green.png" );
		images["crate orange"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "crate-orange.png" );
		images["crate purple"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "crate-purple.png" );
		images["crate red"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "crate-red.png" );
		images["crate yellow"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "crate-yellow.png" );

		images["gate 0 blue"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "gate-blue-right-fg.png" );
		images["gate bg 0 blue"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "gate-blue-right-bg.png" );
		images["gate 1 blue"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "gate-blue-left-fg.png" );
		images["gate bg 1 blue"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "gate-blue-left-bg.png" );

		images["gate 0 green"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "gate-green-right-fg.png" );
		images["gate bg 0 green"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "gate-green-right-bg.png" );
		images["gate 1 green"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "gate-green-left-fg.png" );
		images["gate bg 1 green"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "gate-green-left-bg.png" );

		images["gate 0 orange"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "gate-orange-right-fg.png" );
		images["gate bg 0 orange"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "gate-orange-right-bg.png" );
		images["gate 1 orange"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "gate-orange-left-fg.png" );
		images["gate bg 1 orange"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "gate-orange-left-bg.png" );

		images["gate 0 purple"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "gate-purple-right-fg.png" );
		images["gate bg 0 purple"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "gate-purple-right-bg.png" );
		images["gate 1 purple"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "gate-purple-left-fg.png" );
		images["gate bg 1 purple"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "gate-purple-left-bg.png" );

		images["gate 0 red"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "gate-red-right-fg.png" );
		images["gate bg 0 red"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "gate-red-right-bg.png" );
		images["gate 1 red"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "gate-red-left-fg.png" );
		images["gate bg 1 red"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "gate-red-left-bg.png" );

		images["gate 0 yellow"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "gate-yellow-right-fg.png" );
		images["gate bg 0 yellow"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "gate-yellow-right-bg.png" );
		images["gate 1 yellow"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "gate-yellow-left-fg.png" );
		images["gate bg 1 yellow"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "gate-yellow-left-bg.png" );

		images["truck 0"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "truck_dir0.png" );
		images["truck 1"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "truck_dir1.png" );

		images["button pause"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "button_pause.png", true );
		images["button pause active"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "button_pause_on.png", true );
		images["button quit"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "button_quit.png", true );
		images["button quit active"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "button_quit_on.png", true );

		images["text paused"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "text_paused.png", true );
		images["text fail"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "text_fail.png", true );
		images["text win"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "text_win.png", true );

		images["keyboard"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "keyboard.png" );

		images["star"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "star.png" );
		images["life"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "life.png" );
		images["life shadow"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "life_shadow.png", true );

		// Font - small
		images["0 small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_0_small.png" );
		images["1 small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_1_small.png" );
		images["2 small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_2_small.png" );
		images["3 small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_3_small.png" );
		images["4 small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_4_small.png" );
		images["5 small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_5_small.png" );
		images["6 small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_6_small.png" );
		images["7 small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_7_small.png" );
		images["8 small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_8_small.png" );
		images["9 small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_9_small.png" );
		images["A small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_A_small.png" );
		images["B small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_B_small.png" );
		images["C small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_C_small.png" );
		images["D small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_D_small.png" );
		images["E small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_E_small.png" );
		images["F small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_F_small.png" );
		images["G small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_G_small.png" );
		images["H small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_H_small.png" );
		images["I small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_I_small.png" );
		images["J small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_J_small.png" );
		images["K small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_K_small.png" );
		images["L small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_L_small.png" );
		images["M small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_M_small.png" );
		images["N small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_N_small.png" );
		images["O small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_O_small.png" );
		images["P small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_P_small.png" );
		images["Q small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_Q_small.png" );
		images["R small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_R_small.png" );
		images["S small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_S_small.png" );
		images["T small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_T_small.png" );
		images["U small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_U_small.png" );
		images["V small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_V_small.png" );
		images["W small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_W_small.png" );
		images["X small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_X_small.png" );
		images["Y small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_Y_small.png" );
		images["Z small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_Z_small.png" );
		images["  small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_space_small.png" );
		images["/ small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_slash_small.png" );
		images[". small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_dot_small.png" );
		images[", small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_comma_small.png" );
		images[": small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_colon_small.png" );
		images["; small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_semicolon_small.png" );
		images["- small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_dash_small.png" );
		images["\" small"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_quote_small.png" );

		// Font - medium
		images["0 medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_0_medium.png" );
		images["1 medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_1_medium.png" );
		images["2 medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_2_medium.png" );
		images["3 medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_3_medium.png" );
		images["4 medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_4_medium.png" );
		images["5 medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_5_medium.png" );
		images["6 medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_6_medium.png" );
		images["7 medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_7_medium.png" );
		images["8 medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_8_medium.png" );
		images["9 medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_9_medium.png" );
		images["A medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_A_medium.png" );
		images["B medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_B_medium.png" );
		images["C medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_C_medium.png" );
		images["D medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_D_medium.png" );
		images["E medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_E_medium.png" );
		images["F medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_F_medium.png" );
		images["G medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_G_medium.png" );
		images["H medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_H_medium.png" );
		images["I medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_I_medium.png" );
		images["J medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_J_medium.png" );
		images["K medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_K_medium.png" );
		images["L medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_L_medium.png" );
		images["M medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_M_medium.png" );
		images["N medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_N_medium.png" );
		images["O medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_O_medium.png" );
		images["P medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_P_medium.png" );
		images["Q medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_Q_medium.png" );
		images["R medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_R_medium.png" );
		images["S medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_S_medium.png" );
		images["T medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_T_medium.png" );
		images["U medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_U_medium.png" );
		images["V medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_V_medium.png" );
		images["W medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_W_medium.png" );
		images["X medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_X_medium.png" );
		images["Y medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_Y_medium.png" );
		images["Z medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_Z_medium.png" );
		images["  medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_space_medium.png" );
		images["/ medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_slash_medium.png" );
		images[". medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_dot_medium.png" );
		images[", medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_comma_medium.png" );
		images[": medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_colon_medium.png" );
		images["; medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_semicolon_medium.png" );
		images["- medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_dash_medium.png" );
		images["\" medium"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_quote_medium.png" );

		// Font - large
		images["0 large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_0_large.png" );
		images["1 large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_1_large.png" );
		images["2 large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_2_large.png" );
		images["3 large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_3_large.png" );
		images["4 large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_4_large.png" );
		images["5 large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_5_large.png" );
		images["6 large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_6_large.png" );
		images["7 large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_7_large.png" );
		images["8 large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_8_large.png" );
		images["9 large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_9_large.png" );
		images["A large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_A_large.png" );
		images["B large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_B_large.png" );
		images["C large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_C_large.png" );
		images["D large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_D_large.png" );
		images["E large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_E_large.png" );
		images["F large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_F_large.png" );
		images["G large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_G_large.png" );
		images["H large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_H_large.png" );
		images["I large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_I_large.png" );
		images["J large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_J_large.png" );
		images["K large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_K_large.png" );
		images["L large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_L_large.png" );
		images["M large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_M_large.png" );
		images["N large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_N_large.png" );
		images["O large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_O_large.png" );
		images["P large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_P_large.png" );
		images["Q large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_Q_large.png" );
		images["R large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_R_large.png" );
		images["S large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_S_large.png" );
		images["T large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_T_large.png" );
		images["U large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_U_large.png" );
		images["V large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_V_large.png" );
		images["W large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_W_large.png" );
		images["X large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_X_large.png" );
		images["Y large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_Y_large.png" );
		images["Z large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_Z_large.png" );
		images["  large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_space_large.png" );
		images["/ large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_slash_large.png" );
		images[". large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_dot_large.png" );
		images[", large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_comma_large.png" );
		images[": large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_colon_large.png" );
		images["; large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_semicolon_large.png" );
		images["- large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_dash_large.png" );
		images["\" large"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "font_quote_large.png" );


		// Sound buffers
		sounds["switch"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "snd_button-25.wav" );
		sounds["click"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "snd_button-30.wav" );
		sounds["drive"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "snd_Truck Idle And Pull Off-SoundBible.com-1854979252.wav" );
		sounds["back"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "snd_Backing Up-SoundBible.com-788937884.wav" );
		sounds["crate"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "snd_Closing Drawer-SoundBible.com-1853830442.wav" );
		sounds["point"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "snd_Dropping A Wrench-SoundBible.com-1488523476.wav" );
		sounds["life"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "snd_Door Buzzer-SoundBible.com-1567875395.wav" );
		sounds["fail"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "snd_Not Even Phased-21219-Free-Loops.com.wav" );
		sounds["win"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "snd_Synth Chorus Sounds-21216-Free-Loops.com.wav" );

		// Music files
		music["game over"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "music_Sweet RnB Beat-23820-Free-Loops.com.wav" );
		music["game over"].SetLoop( true );
		music["menu"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "music_Free Hip Hop 3-9480-Free-Loops.com.wav" );
		music["menu"].SetLoop( true );
		music["game"].LoadFromFile( std::string( RESOURCE_BASE_DIR ) + "music_Free Trance Loops 1-9468-Free-Loops.com.wav" );
		music["game"].SetLoop( true );
	}

	gdn::Image& ResourceManager::GetImage( std::string name )
	{
		std::map< std::string, gdn::Image >::iterator result = images.find( name );
		if ( result == images.end() )
		{
			return images["dummy"];
		}
		else
		{
			return result->second;
		}
	}

	gdn::SoundBuffer& ResourceManager::GetSound( std::string name )
	{
		std::map< std::string, gdn::SoundBuffer >::iterator result = sounds.find( name );
		if ( result == sounds.end() )
		{
			return sounds["dummy"];
		}
		else
		{
			return result->second;
		}
	}

	gdn::Music& ResourceManager::GetMusic( std::string name )
	{
		std::map< std::string, gdn::Music >::iterator result = music.find( name );
		if ( result == music.end() )
		{
			return music["dummy"];
		}
		else
		{
			return result->second;
		}
	}
}
