#include "SceneHighscore.h"

#include "Functions.h"

#include <fstream>
#include <sstream>
#include <list>
#include <iostream>
using namespace std;


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
	newScore = NULL;
	newTextName = NULL;

	std::list< Score* >::iterator it;
	std::ifstream myfile ("highscores.wph");
	if (myfile.is_open())
	{
		while (!myfile.eof() )
		{
			std::string line;
			getline(myfile, line);
			size_t equals = line.find("=");
			int thescore;
			StringToInt(line.substr(0, equals), thescore);
			std::string thename = line.substr(equals + 1);
			InsertScore( new Score(thescore, thename) );
		}
		myfile.close();
	}
	else
	{
		InsertScore( new Score( 3 * 25, "Noob" ) );
		InsertScore( new Score( 5 * 25, "Newbie" ) );
		InsertScore( new Score( 10 * 25, "Average Joe" ) );
		InsertScore( new Score( 25 * 25, "L337" ) );
		InsertScore( new Score( 30 * 25, "u9" ) );
		InsertScore( new Score( 40 * 25, "wannabe" ) );
		InsertScore( new Score( 50 * 25, "mr glasses" ) );
		InsertScore( new Score( 75 * 25, "Spacechase0" ) );
		InsertScore( new Score( 100 * 25, "Your mom" ) );
		InsertScore( new Score( 150 * 25, "Hartnell" ) );
	}

	// Any event for highscore scene?
	while ( EventMgr.HasEvent( gdn::HIGHSCORE ) )
	{
		ResMgr.GetMusic( "game over" ).Play();
		gdn::GameEvent& event = EventMgr.PeekEvent( gdn::HIGHSCORE );
		switch ( event.type )
		{
			case gdn::GameEvent::Highscore:
				if ( scores.back()->score < event.Highscore_new_score )
				{
					keyboard = new Keyboard();
					keyboard->Show();
					newScore = new Score( event.Highscore_new_score, "" );
					InsertScore( newScore );
				}
				break;

			default:
				break;
		}
		EventMgr.PopEvent( gdn::HIGHSCORE );
	}

	highscore_title = Text( std::string( "HIGHSCORES" ), 0, 0, Text::LARGE );
	highscore_title.SetPosition( App.GetWidth() / 2 - highscore_title.GetWidth() / 2.0f, 2.0f );

	int str_sofar = 0;
	for (std::list< Score* >::iterator it = scores.begin(); it != scores.end(); it++)
	{
		if (str_sofar < 10)
		{
			highscores.push_back( new Text(std::string((*it)->name), 40, str_sofar * 20 + 35, Text::MEDIUM) );

			// Get a handle where we can put name after typing (if applicable)
			if ( *it == newScore )
				newTextName = highscores.back();

			std::stringstream thescore;
			thescore << (*it)->score;
			highscores.push_back( new Text(thescore.str(), 0, 0, Text::MEDIUM) );
			highscores.back()->SetPosition( App.GetWidth() - highscores.back()->GetWidth() - 40, str_sofar * 20 + 35 );
		}
		str_sofar += 1;
	}
}

void SceneHighscore::Terminate()
{
	if ( keyboard )
		delete keyboard;
	keyboard = NULL;
	if (ResMgr.GetMusic( "game over" ).GetStatus() == sf::Music::Playing)
	{
		ResMgr.GetMusic( "game over" ).Stop();
	}

	for ( std::list<Score*>::iterator it = scores.begin(); it != scores.end(); ++it )
		delete *it;
	scores.clear();

	for ( std::vector<Text*>::iterator it = highscores.begin(); it != highscores.end(); ++it )
		delete *it;
	highscores.clear();
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
				newScore->name = keyboard->GetText();
				newTextName->SetText( newScore->name );
				keyboard->Hide();
				isMouseDown = true;

				std::ofstream file("highscores.wph", std::ios::out | std::ios::trunc);
				int str_sofar = 0;
				for (std::list< Score* >::iterator it = scores.begin(); it != scores.end(); it++)
				{
					if (str_sofar < 10)
					{
						file << (*it)->score << "=" << (*it)->name << std::endl;
					}
					str_sofar += 1;
				}
				file.close();
			}
		}
	}

	// Ignore everything if keyboard is shown
	if ( keyboard == NULL or !keyboard->IsShown() )
	{
		bool curMouseDown = App.GetWindow().IsMouseButtonDown();
		if ( curMouseDown and !isMouseDown )
		{
			sndClick.Play();
			EventMgr.PushEvent( gdn::ENGINE, gdn::GameEvent::ChangeSceneEvent( "menu" ) );
		}
		isMouseDown = curMouseDown;
	}
}

void SceneHighscore::Draw()
{
	App.GetWindow().Clear( 0, 0, 0 );

	for (int i = 0; i < (int)highscores.size(); i++)
	{
		highscores[i]->Draw();
	}

	if ( keyboard )
		keyboard->Draw();
}

void SceneHighscore::InsertScore( Score* score )
{
	scores.push_back( score );
	scores.sort( ScoreSort );
}



// This makes sure the scene is added to the engine!
SceneHighscore* highscore = new SceneHighscore();
