#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <string>
#include <list>
#include <map>

#define EventMgr (*(gdn::EventManager::GetInstance()))

namespace gdn
{
	// Add receiver here if you want to listen to some specific events
	enum EVENT_RECEIVER
	{
		ENGINE, // Used to change scenes, quit etc.
		GAME, // Used for changing levels
		HIGHSCORE, // Used if there was a new highscore and player should enter name
		count // Not used
	};



	class GameEvent
	{
	public:
		// Add event type here if you need another event type to listen for
		enum EventType
		{
			ChangeScene,
			Highscore,
			Quit,
			count // Not used
		};
		EventType type;

		// Add any data your new eventtype might need here
		union
		{
			std::string* ChangeScene_name;
			int Highscore_new_score;
		};

		// If any of your events has a different kind of data you need to create a constructor for that datatype
		GameEvent( EventType t, std::string data ) : type( t )
		{
			ChangeScene_name = new std::string( data );
		}
		GameEvent( EventType t, int data ) : type( t )
		{
			Highscore_new_score = data;
		}
		GameEvent( EventType t ) : type( t )
		{
		}
		GameEvent( const GameEvent& other )
		{
			if ( other.type == GameEvent::ChangeScene )
			{
				ChangeScene_name = new std::string( *other.ChangeScene_name );
			}
			else
			{
				Highscore_new_score = other.Highscore_new_score;
			}
			type = other.type;
		}
		~GameEvent()
		{
			if ( type == GameEvent::ChangeScene )
				delete ChangeScene_name;
		}

		static GameEvent ChangeSceneEvent( std::string newscene );
		static GameEvent HighscoreEvent( int newscore );
		static GameEvent QuitEvent();
	};





	class EventManager
	{
	public:
		static EventManager* GetInstance();

		void PushEvent( EVENT_RECEIVER receiver, GameEvent event );
		bool HasEvent( EVENT_RECEIVER receiver );
		GameEvent& PeekEvent( EVENT_RECEIVER receiver );
		void PopEvent( EVENT_RECEIVER receiver );

	protected:
		EventManager(); // constructor
		~EventManager();
		void Initialize();

	private:
		static EventManager* instance;
		std::map< EVENT_RECEIVER, std::list< GameEvent > > events;
	};
}

#endif // EVENTMANAGER_H
