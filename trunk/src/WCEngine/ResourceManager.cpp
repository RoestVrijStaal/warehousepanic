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
		images["splash"].LoadFromFile( "media/bg_splash.png" );
		images["title"].LoadFromFile( "media/bg_title.png" );
		images["general"].LoadFromFile( "media/bg_general.png" );
		images["level"].LoadFromFile( "media/bg_level.png" );
		images["tutorial 1"].LoadFromFile( "media/bg_tutorial_1.png" );
		images["tutorial 2"].LoadFromFile( "media/bg_tutorial_2.png" );
		images["tutorial 3"].LoadFromFile( "media/bg_tutorial_3.png" );
		images["tutorial 4"].LoadFromFile( "media/bg_tutorial_4.png" );
		images["tile"].LoadFromFile( "media/tile.png" );

		// Game graphics
		images["conveyor 02"].LoadFromFile( "media/conveyor_dir_02.png" );
		images["conveyor 13"].LoadFromFile( "media/conveyor_dir_13.png" );
		images["conveyor 02 con 1"].LoadFromFile( "media/conveyor_dir_02_con_1.png" );
		images["conveyor 02 con 3"].LoadFromFile( "media/conveyor_dir_02_con_3.png" );
		images["conveyor 13 con 0"].LoadFromFile( "media/conveyor_dir_13_con_0.png" );
		images["conveyor 13 con 2"].LoadFromFile( "media/conveyor_dir_13_con_2.png" );
		images["conveyor 02 cross"].LoadFromFile( "media/conveyor_dir_02_cross.png" );
		images["conveyor 13 cross"].LoadFromFile( "media/conveyor_dir_13_cross.png" );
		images["conveyor 0 turn"].LoadFromFile( "media/conveyor_dir_0_turn.png" );
		images["conveyor 1 turn"].LoadFromFile( "media/conveyor_dir_1_turn.png" );
		images["conveyor 2 turn"].LoadFromFile( "media/conveyor_dir_2_turn.png" );
		images["conveyor 3 turn"].LoadFromFile( "media/conveyor_dir_3_turn.png" );
		images["conveyor 0 turn high"].LoadFromFile( "media/conveyor_dir_0_turn_high.png" );
		images["conveyor 1 turn high"].LoadFromFile( "media/conveyor_dir_1_turn_high.png" );
		images["conveyor 2 turn high"].LoadFromFile( "media/conveyor_dir_2_turn_high.png" );
		images["conveyor 3 turn high"].LoadFromFile( "media/conveyor_dir_3_turn_high.png" );

		images["crate blue"].LoadFromFile( "media/crate-blue.png" );
		images["crate green"].LoadFromFile( "media/crate-green.png" );
		images["crate orange"].LoadFromFile( "media/crate-orange.png" );
		images["crate purple"].LoadFromFile( "media/crate-purple.png" );
		images["crate red"].LoadFromFile( "media/crate-red.png" );
		images["crate yellow"].LoadFromFile( "media/crate-yellow.png" );

		images["gate 0 blue"].LoadFromFile( "media/gate-blue-right-fg.png" );
		images["gate bg 0 blue"].LoadFromFile( "media/gate-blue-right-bg.png" );
		images["gate 1 blue"].LoadFromFile( "media/gate-blue-left-fg.png" );
		images["gate bg 1 blue"].LoadFromFile( "media/gate-blue-left-bg.png" );

		images["gate 0 green"].LoadFromFile( "media/gate-green-right-fg.png" );
		images["gate bg 0 green"].LoadFromFile( "media/gate-green-right-bg.png" );
		images["gate 1 green"].LoadFromFile( "media/gate-green-left-fg.png" );
		images["gate bg 1 green"].LoadFromFile( "media/gate-green-left-bg.png" );

		images["gate 0 orange"].LoadFromFile( "media/gate-orange-right-fg.png" );
		images["gate bg 0 orange"].LoadFromFile( "media/gate-orange-right-bg.png" );
		images["gate 1 orange"].LoadFromFile( "media/gate-orange-left-fg.png" );
		images["gate bg 1 orange"].LoadFromFile( "media/gate-orange-left-bg.png" );

		images["gate 0 purple"].LoadFromFile( "media/gate-purple-right-fg.png" );
		images["gate bg 0 purple"].LoadFromFile( "media/gate-purple-right-bg.png" );
		images["gate 1 purple"].LoadFromFile( "media/gate-purple-left-fg.png" );
		images["gate bg 1 purple"].LoadFromFile( "media/gate-purple-left-bg.png" );

		images["gate 0 red"].LoadFromFile( "media/gate-red-right-fg.png" );
		images["gate bg 0 red"].LoadFromFile( "media/gate-red-right-bg.png" );
		images["gate 1 red"].LoadFromFile( "media/gate-red-left-fg.png" );
		images["gate bg 1 red"].LoadFromFile( "media/gate-red-left-bg.png" );

		images["gate 0 yellow"].LoadFromFile( "media/gate-yellow-right-fg.png" );
		images["gate bg 0 yellow"].LoadFromFile( "media/gate-yellow-right-bg.png" );
		images["gate 1 yellow"].LoadFromFile( "media/gate-yellow-left-fg.png" );
		images["gate bg 1 yellow"].LoadFromFile( "media/gate-yellow-left-bg.png" );

		images["truck 0"].LoadFromFile( "media/truck_dir0.png" );
		images["truck 1"].LoadFromFile( "media/truck_dir1.png" );

		images["button pause"].LoadFromFile( "media/button_pause.png" );
		images["button pause active"].LoadFromFile( "media/button_pause_on.png" );
		images["button quit"].LoadFromFile( "media/button_quit.png" );
		images["button quit active"].LoadFromFile( "media/button_quit_on.png" );

		images["text paused"].LoadFromFile( "media/text_paused.png" );
		images["text fail"].LoadFromFile( "media/text_fail.png" );
		images["text win"].LoadFromFile( "media/text_win.png" );

		images["keyboard"].LoadFromFile( "media/keyboard.png" );

		images["star"].LoadFromFile( "media/star.png" );

		// Font - small
		images["0 small"].LoadFromFile( "media/font_0_small.png" );
		images["1 small"].LoadFromFile( "media/font_1_small.png" );
		images["2 small"].LoadFromFile( "media/font_2_small.png" );
		images["3 small"].LoadFromFile( "media/font_3_small.png" );
		images["4 small"].LoadFromFile( "media/font_4_small.png" );
		images["5 small"].LoadFromFile( "media/font_5_small.png" );
		images["6 small"].LoadFromFile( "media/font_6_small.png" );
		images["7 small"].LoadFromFile( "media/font_7_small.png" );
		images["8 small"].LoadFromFile( "media/font_8_small.png" );
		images["9 small"].LoadFromFile( "media/font_9_small.png" );
		images["A small"].LoadFromFile( "media/font_A_small.png" );
		images["B small"].LoadFromFile( "media/font_B_small.png" );
		images["C small"].LoadFromFile( "media/font_C_small.png" );
		images["D small"].LoadFromFile( "media/font_D_small.png" );
		images["E small"].LoadFromFile( "media/font_E_small.png" );
		images["F small"].LoadFromFile( "media/font_F_small.png" );
		images["G small"].LoadFromFile( "media/font_G_small.png" );
		images["H small"].LoadFromFile( "media/font_H_small.png" );
		images["I small"].LoadFromFile( "media/font_I_small.png" );
		images["J small"].LoadFromFile( "media/font_J_small.png" );
		images["K small"].LoadFromFile( "media/font_K_small.png" );
		images["L small"].LoadFromFile( "media/font_L_small.png" );
		images["M small"].LoadFromFile( "media/font_M_small.png" );
		images["N small"].LoadFromFile( "media/font_N_small.png" );
		images["O small"].LoadFromFile( "media/font_O_small.png" );
		images["P small"].LoadFromFile( "media/font_P_small.png" );
		images["Q small"].LoadFromFile( "media/font_Q_small.png" );
		images["R small"].LoadFromFile( "media/font_R_small.png" );
		images["S small"].LoadFromFile( "media/font_S_small.png" );
		images["T small"].LoadFromFile( "media/font_T_small.png" );
		images["U small"].LoadFromFile( "media/font_U_small.png" );
		images["V small"].LoadFromFile( "media/font_V_small.png" );
		images["W small"].LoadFromFile( "media/font_W_small.png" );
		images["X small"].LoadFromFile( "media/font_X_small.png" );
		images["Y small"].LoadFromFile( "media/font_Y_small.png" );
		images["Z small"].LoadFromFile( "media/font_Z_small.png" );
		images["  small"].LoadFromFile( "media/font_space_small.png" );
		images["/ small"].LoadFromFile( "media/font_slash_small.png" );
		images[". small"].LoadFromFile( "media/font_dot_small.png" );
		images[": small"].LoadFromFile( "media/font_colon_small.png" );
		images["- small"].LoadFromFile( "media/font_dash_small.png" );

		// Font - medium
		images["0 medium"].LoadFromFile( "media/font_0_medium.png" );
		images["1 medium"].LoadFromFile( "media/font_1_medium.png" );
		images["2 medium"].LoadFromFile( "media/font_2_medium.png" );
		images["3 medium"].LoadFromFile( "media/font_3_medium.png" );
		images["4 medium"].LoadFromFile( "media/font_4_medium.png" );
		images["5 medium"].LoadFromFile( "media/font_5_medium.png" );
		images["6 medium"].LoadFromFile( "media/font_6_medium.png" );
		images["7 medium"].LoadFromFile( "media/font_7_medium.png" );
		images["8 medium"].LoadFromFile( "media/font_8_medium.png" );
		images["9 medium"].LoadFromFile( "media/font_9_medium.png" );
		images["A medium"].LoadFromFile( "media/font_A_medium.png" );
		images["B medium"].LoadFromFile( "media/font_B_medium.png" );
		images["C medium"].LoadFromFile( "media/font_C_medium.png" );
		images["D medium"].LoadFromFile( "media/font_D_medium.png" );
		images["E medium"].LoadFromFile( "media/font_E_medium.png" );
		images["F medium"].LoadFromFile( "media/font_F_medium.png" );
		images["G medium"].LoadFromFile( "media/font_G_medium.png" );
		images["H medium"].LoadFromFile( "media/font_H_medium.png" );
		images["I medium"].LoadFromFile( "media/font_I_medium.png" );
		images["J medium"].LoadFromFile( "media/font_J_medium.png" );
		images["K medium"].LoadFromFile( "media/font_K_medium.png" );
		images["L medium"].LoadFromFile( "media/font_L_medium.png" );
		images["M medium"].LoadFromFile( "media/font_M_medium.png" );
		images["N medium"].LoadFromFile( "media/font_N_medium.png" );
		images["O medium"].LoadFromFile( "media/font_O_medium.png" );
		images["P medium"].LoadFromFile( "media/font_P_medium.png" );
		images["Q medium"].LoadFromFile( "media/font_Q_medium.png" );
		images["R medium"].LoadFromFile( "media/font_R_medium.png" );
		images["S medium"].LoadFromFile( "media/font_S_medium.png" );
		images["T medium"].LoadFromFile( "media/font_T_medium.png" );
		images["U medium"].LoadFromFile( "media/font_U_medium.png" );
		images["V medium"].LoadFromFile( "media/font_V_medium.png" );
		images["W medium"].LoadFromFile( "media/font_W_medium.png" );
		images["X medium"].LoadFromFile( "media/font_X_medium.png" );
		images["Y medium"].LoadFromFile( "media/font_Y_medium.png" );
		images["Z medium"].LoadFromFile( "media/font_Z_medium.png" );
		images["  medium"].LoadFromFile( "media/font_space_medium.png" );
		images["/ medium"].LoadFromFile( "media/font_slash_medium.png" );
		images[". medium"].LoadFromFile( "media/font_dot_medium.png" );
		images[": medium"].LoadFromFile( "media/font_colon_medium.png" );
		images["- medium"].LoadFromFile( "media/font_dash_medium.png" );

		// Font - large
		images["0 large"].LoadFromFile( "media/font_0_large.png" );
		images["1 large"].LoadFromFile( "media/font_1_large.png" );
		images["2 large"].LoadFromFile( "media/font_2_large.png" );
		images["3 large"].LoadFromFile( "media/font_3_large.png" );
		images["4 large"].LoadFromFile( "media/font_4_large.png" );
		images["5 large"].LoadFromFile( "media/font_5_large.png" );
		images["6 large"].LoadFromFile( "media/font_6_large.png" );
		images["7 large"].LoadFromFile( "media/font_7_large.png" );
		images["8 large"].LoadFromFile( "media/font_8_large.png" );
		images["9 large"].LoadFromFile( "media/font_9_large.png" );
		images["A large"].LoadFromFile( "media/font_A_large.png" );
		images["B large"].LoadFromFile( "media/font_B_large.png" );
		images["C large"].LoadFromFile( "media/font_C_large.png" );
		images["D large"].LoadFromFile( "media/font_D_large.png" );
		images["E large"].LoadFromFile( "media/font_E_large.png" );
		images["F large"].LoadFromFile( "media/font_F_large.png" );
		images["G large"].LoadFromFile( "media/font_G_large.png" );
		images["H large"].LoadFromFile( "media/font_H_large.png" );
		images["I large"].LoadFromFile( "media/font_I_large.png" );
		images["J large"].LoadFromFile( "media/font_J_large.png" );
		images["K large"].LoadFromFile( "media/font_K_large.png" );
		images["L large"].LoadFromFile( "media/font_L_large.png" );
		images["M large"].LoadFromFile( "media/font_M_large.png" );
		images["N large"].LoadFromFile( "media/font_N_large.png" );
		images["O large"].LoadFromFile( "media/font_O_large.png" );
		images["P large"].LoadFromFile( "media/font_P_large.png" );
		images["Q large"].LoadFromFile( "media/font_Q_large.png" );
		images["R large"].LoadFromFile( "media/font_R_large.png" );
		images["S large"].LoadFromFile( "media/font_S_large.png" );
		images["T large"].LoadFromFile( "media/font_T_large.png" );
		images["U large"].LoadFromFile( "media/font_U_large.png" );
		images["V large"].LoadFromFile( "media/font_V_large.png" );
		images["W large"].LoadFromFile( "media/font_W_large.png" );
		images["X large"].LoadFromFile( "media/font_X_large.png" );
		images["Y large"].LoadFromFile( "media/font_Y_large.png" );
		images["Z large"].LoadFromFile( "media/font_Z_large.png" );
		images["  large"].LoadFromFile( "media/font_space_large.png" );
		images["/ large"].LoadFromFile( "media/font_slash_large.png" );
		images[". large"].LoadFromFile( "media/font_dot_large.png" );
		images[": large"].LoadFromFile( "media/font_colon_large.png" );
		images["- large"].LoadFromFile( "media/font_dash_large.png" );

		// Sound buffers
		sounds["switch"].LoadFromFile( "media/snd_button-25.wav" );
		sounds["click"].LoadFromFile( "media/snd_button-30.wav" );
		sounds["drive"].LoadFromFile( "media/snd_Truck Idle And Pull Off-SoundBible.com-1854979252.wav" );
		sounds["back"].LoadFromFile( "media/snd_Backing Up-SoundBible.com-788937884.wav" );
		sounds["crate"].LoadFromFile( "media/snd_Closing Drawer-SoundBible.com-1853830442.wav" );
		sounds["point"].LoadFromFile( "media/snd_Dropping A Wrench-SoundBible.com-1488523476.wav" );
		sounds["fail"].LoadFromFile( "media/snd_Not Even Phased-21219-Free-Loops.com.wav" );
		sounds["win"].LoadFromFile( "media/snd_Synth Chorus Sounds-21216-Free-Loops.com.wav" );

		// Music files
		music["game over"].LoadFromFile( "media/music_Sweet RnB Beat-23820-Free-Loops.com.wav" );
		music["game over"].SetLoop( true );
		music["menu"].LoadFromFile( "media/music_Free Hip Hop 3-9480-Free-Loops.com.wav" );
		music["menu"].SetLoop( true );
		music["game"].LoadFromFile( "media/music_Free Trance Loops 1-9468-Free-Loops.com.wav" );
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
