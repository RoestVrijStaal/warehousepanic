#include "EventManager.h"

namespace gdn
{
	// Easier constructors for typical events
	GameEvent GameEvent::ChangeSceneEvent( std::string newscene )
	{
		return GameEvent( ChangeScene, newscene );
	}
	GameEvent GameEvent::HighscoreEvent( int newscore )
	{
		return GameEvent( Highscore, newscore );
	}
	GameEvent GameEvent::ChangeLevelEvent( int nlevel, int cscore )
	{
	    EventMgr.PushEvent( gdn::HIGHSCORE, gdn::GameEvent::HighscoreEvent( cscore ) );
	    return GameEvent( ChangeLevel, nlevel/*, cscore*/ );
	}
	GameEvent GameEvent::QuitEvent()
	{
		return GameEvent( Quit );
	}





	EventManager* EventManager::instance = NULL;

	EventManager* EventManager::GetInstance()
	{
		if ( instance == NULL )
		{
			instance = new EventManager();
		}
		return instance;
	}

	EventManager::EventManager()
	{
		Initialize();
	}

	EventManager::~EventManager()
	{
		if ( instance != NULL )
		{
			delete instance;
			instance = NULL;
		}
	}

	void EventManager::Initialize()
	{
		for ( EVENT_RECEIVER i = (EVENT_RECEIVER)0; i < count; i = (EVENT_RECEIVER)(i + 1) )
		{
			events[i];
		}
	}

	void EventManager::PushEvent( EVENT_RECEIVER receiver, GameEvent event )
	{
		std::list< GameEvent >& queue = events[receiver];
		queue.push_back( event );
	}

	bool EventManager::HasEvent( EVENT_RECEIVER receiver )
	{
		std::list< GameEvent >& queue = events[receiver];
		return queue.size() > 0;
	}

	GameEvent& EventManager::PeekEvent( EVENT_RECEIVER receiver )
	{
		std::list< GameEvent >& queue = events[receiver];
		return queue.front();
	}

	void EventManager::PopEvent( EVENT_RECEIVER receiver )
	{
		std::list< GameEvent >& queue = events[receiver];
		queue.pop_front();
	}
}
