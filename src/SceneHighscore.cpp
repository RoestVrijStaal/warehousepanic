#include "SceneHighscore.h"

#include "WCEngine/Application.h"
#include "WCEngine/EventManager.h"
#include "WCEngine/ResourceManager.h"
#include "Functions.h"

#include <fstream>
#include <sstream>
#include <list>


// Constructors
SceneHighscore::SceneHighscore() : Scene( "highscore" )
{
}

SceneHighscore::~SceneHighscore()
{
}



// Methods
void SceneHighscore::Initialize()
{
	sndClick = sf::Sound( ResMgr.GetSound( "click" ) );
	isMouseDown = true;
	keyboard = NULL;
	newScore = 0;
	name = "";

	std::list< Score >::iterator it;
    bool tmp = false;
    std::ifstream myfile ("highscores.wph");
    if (myfile.is_open())
    {
        while (! myfile.eof() )
        {
            std::string line;
            getline(myfile,line);
            size_t equals = line.find("=");
            int thescore;
            StringToInt(line.substr(0,equals),thescore);
            std::string thename = line.substr(equals + 1);
            bool stop = false;
            std::list< Score >::iterator it = scores.end();
            while (stop == false)
            {
                if (it->score < newScore)
                {
                    it--;
                }
                else
                {
                    stop = true;
                }
            }
            scores.insert( it, 1, Score(thescore, thename) );
        }
        myfile.close();
    }
    else
    {
        scores.insert( scores.begin(),1,Score( 3 * 25, "MILESTOE MARKER" ) );
        scores.insert( scores.begin(),1,Score( 5 * 25, "MILESTOE MARKER" ) );
        scores.insert( scores.begin(),1,Score( 10 * 25, "MILESTOE MARKER" ) );
        scores.insert( scores.begin(),1,Score( 25 * 25, "MILESTOE MARKER" ) );
        scores.insert( scores.begin(),1,Score( 30 * 25, "MILESTOE MARKER" ) );
        scores.insert( scores.begin(),1,Score( 40 * 25, "MILESTOE MARKER" ) );
        scores.insert( scores.begin(),1,Score( 50 * 25, "MILESTOE MARKER" ) );
        scores.insert( scores.begin(),1,Score( 75 * 25, "MILESTOE MARKER" ) );
        scores.insert( scores.begin(),1,Score( 100 * 25, "MILESTOE MARKER" ) );
        scores.insert( scores.begin(),1,Score( 150 * 25, "MILESTOE MARKER" ) );
    }

	// Any event for highscore scene?
	while ( EventMgr.HasEvent( HIGHSCORE ) )
	{
		GameEvent& event = EventMgr.PeekEvent( HIGHSCORE );
		switch ( event.type )
		{
			case GameEvent::Highscore:
				// Reached highscore table from game, so play music depending on how well they did.
				newScore = event.Highscore_new_score;
				for (it = scores.begin(); it != scores.end(); it++)
				{
				    if (newScore > it->score)
				    {
				        tmp = true;
				    }
				}
				if (tmp == true)
				{
                    ResMgr.GetMusic( "new highscore" ).Play();
                    keyboard = new Keyboard();
					keyboard->Show();
					didChange = true;
				}
				else
				{
                    ResMgr.GetMusic( "game over" ).Play();
				}
				break;

			default:
				break;
		}
		EventMgr.PopEvent( HIGHSCORE );
	}
    highscore_title = Text( std::string( "HIGHSCORES" ), 0, 0, Text::LARGE );
    highscore_title.SetPosition( 320 - highscore_title.GetRect().GetWidth(), 2 );
    int str_sofar = 0;
	for (std::list< Score >::iterator it = scores.begin(); it != scores.end(); it++)
	{
	    if (str_sofar < 10)
	    {
            highscores.push_back( Text(std::string(it->name), 40, str_sofar * 20 + 35, Text::MEDIUM) );
            highscores.back().SetPosition( 40, str_sofar * 20 + 35 );
            std::stringstream thescore;
            thescore << it->score;
            highscores.push_back( Text(thescore.str(), 225, str_sofar * 20 + 35, Text::MEDIUM) );
            highscores.back().SetPosition( 225, str_sofar * 20 + 35 );
	    }
	    str_sofar += 1;
	}
}

void SceneHighscore::Terminate()
{
	if ( keyboard )
		delete keyboard;
	keyboard = NULL;
	if (ResMgr.GetMusic( "new highscore" ).GetStatus() == sf::Music::Playing)
	{
	    ResMgr.GetMusic( "new highscore" ).Stop();
	}
	else if (ResMgr.GetMusic( "game over" ).GetStatus() == sf::Music::Playing)
	{
	    ResMgr.GetMusic( "game over" ).Stop();
	}
	scores.clear();
}

void SceneHighscore::Step()
{
	if ( keyboard )
	{
		keyboard->Step();
		if ( keyboard->IsShown() )
		{
			// User pressed enter?
			if ( keyboard->IsDone() )
			{
				name = keyboard->GetText();
				keyboard->Hide();
				isMouseDown = true;
				std::list< Score >::iterator it;
				int sofar = 0;
				for (it = scores.begin(); it != scores.end(); it++)
				{
				    if (it->score >= newScore)
				    {
				        sofar += 1;
				        continue;
				    }
				    break;
				}
				std::list< Score >::iterator it2 = scores.begin();
				while (sofar > 0)
				{
				    it2++;
				    sofar--;
				}
				scores.insert( it2, 1, Score(newScore, name) );
                std::ofstream file("highscores.wph",std::ios::out | std::ios::trunc);
                int str_sofar = 0;
                for (std::list< Score >::iterator it = scores.begin(); it != scores.end(); it++)
                {
                    if (str_sofar < 10)
                    {
                        file << it->score << "=" << it->name << std::endl;
                    }
                    str_sofar += 1;
                }
                file.close();
                didChange = false;
			}
		}
	}

	// Ignore everything if keyboard is shown
	if ( keyboard == NULL or !keyboard->IsShown() )
	{
		bool curMouseDown = App.GetWindow().GetInput().IsMouseButtonDown( sf::Mouse::Left );
		if ( curMouseDown and !isMouseDown )
		{
			sndClick.Play();
			EventMgr.PushEvent( ENGINE, GameEvent::ChangeSceneEvent( "menu" ) );
		}
		isMouseDown = curMouseDown;
	}
}

void SceneHighscore::Draw()
{
	App.GetWindow().Clear( sf::Color( 0, 0, 0 ) );

	highscore_title.Draw();
	for (int i = 0; i < (int)highscores.size(); i++)
	{
	    highscores[i].Draw();
	}

	if ( keyboard )
		keyboard->Draw();
}



// This makes sure the scene is added to the engine!
SceneHighscore* highscore = new SceneHighscore();
