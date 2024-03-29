#include "SceneHighscore.h"

#include "Functions.h"

#include <algorithm>
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
	//cout << "Highscore::Initializing" << endl;
	sndClick = gdn::Sound( ResMgr.GetSound( "click" ) );
	isMouseDown = true;
	keyboard = NULL;
	newScore = NULL;
	newTextName = NULL;
	timer = 0;

	bg_general = gdn::Sprite( ResMgr.GetImage( "general" ) );

	std::list< Score* >::iterator it;
	//cout << "Highscore::Opening file" << endl;
	std::ifstream myfile ("highscores.wph");
	if (myfile.is_open())
	{
		//cout << "Highscore::File opened" << endl;
		while (!myfile.eof() )
		{
			std::string line;
			getline(myfile, line);
			//cout << "Highscore::line: " << line << endl;
			size_t equals = line.find("=");
			int thescore;
			StringToInt(line.substr(0, equals), thescore);
			std::string thename = line.substr(equals + 1);
			//cout << "Highscore::inserting score " << thescore << " with name " << thename << endl;
			InsertScore( new Score(thescore, thename) );
		}
		//cout << "Highscore::closing file" << endl;
		myfile.close();
	}
	else
	{
		//cout << "Highscore::Inserting default highscore table" << endl;
		InsertScore( new Score( 10 * 25, "Noob" ) );
		InsertScore( new Score( 50 * 25, "Newbie" ) );
		InsertScore( new Score( 100 * 25, "Novice" ) );
		InsertScore( new Score( 200 * 25, "mr L337" ) );
		InsertScore( new Score( 300 * 25, "Average Joe" ) );
		InsertScore( new Score( 400 * 25, "Uni" ) );
		InsertScore( new Score( 500 * 25, "mr glasses" ) );
		InsertScore( new Score( 650 * 25, "Spacechase0" ) );
		InsertScore( new Score( 800 * 25, "Hartnell" ) );
		InsertScore( new Score( 1000 * 25, "Your mom" ) );
	}

	// Any event for highscore scene?
	//cout << "Highscore::Loop through events" << endl;
	while ( EventMgr.HasEvent( gdn::HIGHSCORE ) )
	{
		//cout << "Highscore::Play gameover music" << endl;
		ResMgr.GetMusic( "game over" ).Play();
		//cout << "Highscore::Peek event and switch on it" << endl;
		gdn::GameEvent& event = EventMgr.PeekEvent( gdn::HIGHSCORE );
		switch ( event.type )
		{
			case gdn::GameEvent::Highscore:
				//cout << "Highscore::Check score against poorest score" << scores.back()->score << endl;
				if ( scores.back()->score < event.Highscore_new_score )
				{
					//cout << "Highscore:: New highscore, creating keyboard" << endl;
					keyboard = new Keyboard();
					//cout << "Highscore::show keyboard" << endl;
					keyboard->Show();
					//cout << "Highscore::insert new score into list" << endl;
					newScore = new Score( event.Highscore_new_score, "" );
					InsertScore( newScore );
				}
				break;

			default:
				break;
		}
		EventMgr.PopEvent( gdn::HIGHSCORE );
	}

	//cout << "Highscore::create title text" << endl;
	highscore_title = Text( std::string( "HIGHSCORES" ), 0, 0, Text::LARGE );
	highscore_title.SetPosition( App.GetWidth() / 2 - highscore_title.GetWidth() / 2.0f, 2.0f );

	int str_sofar = 0;
	//cout << "Highscore::loop through scores making text" << endl;
	for (std::list< Score* >::iterator it = scores.begin(); it != scores.end(); it++)
	{
		//cout << "Highscore:: so far: " << str_sofar << endl;
		if (str_sofar < 10)
		{
			std::stringstream number;
			number << str_sofar + 1 << ".";
			highscores.push_back( new Text(number.str(), 30, str_sofar * 20 + 35, Text::MEDIUM) );
			highscores.push_back( new Text(std::string((*it)->name), 60, str_sofar * 20 + 35, Text::MEDIUM) );

			// Get a handle where we can put name after typing (if applicable)
			if ( *it == newScore )
				newTextName = highscores.back();

			highscores.push_back( new Text(FormatNumber((*it)->score), 0, 0, Text::MEDIUM) );
			highscores.back()->SetPosition( App.GetWidth() - highscores.back()->GetWidth() - 30, str_sofar * 20 + 35 );
		}
		str_sofar += 1;
	}
	//cout << "Highscore::initialize done" << endl;
}

void SceneHighscore::Terminate()
{
	if ( keyboard )
		delete keyboard;
	keyboard = NULL;
	if ( ResMgr.GetMusic( "game over" ).IsPlaying() )
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
	if ( timer > 0 )
		--timer;

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
				timer = (int)(App.GetFPS() * 5);

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

    App.GetWindow().Draw( bg_general );

    highscore_title.Draw();

	for (int i = 0; i < (int)highscores.size(); i++)
	{
		if ( newTextName == highscores[i] )
			if ( timer / 60 % 2 )
				continue;
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

std::string SceneHighscore::FormatNumber( int num )
{
	std::stringstream res;
	int idx = 0;
	while ( num > 0 )
	{
		if ( idx % 3 == 0 )
			res << ".";

		res << num % 10;
		num /= 10;
		++idx;
	}
	std::string toReverse = res.str().substr(1);
	reverse( toReverse.begin(), toReverse.end() );
	return toReverse;
}

// This makes sure the scene is added to the engine!
SceneHighscore* highscore = new SceneHighscore();
