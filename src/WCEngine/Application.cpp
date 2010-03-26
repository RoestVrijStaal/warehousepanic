#include "Application.h"

#include "SDL/SDL.h"

#include "EventManager.h"
#include "Scene.h"
#include "Timer.h"
#include <ctime>
#include <cstdlib>
#include <sstream>

namespace gdn
{
	Application* Application::instance = NULL;

	Application* Application::GetInstance()
	{
		if ( instance == NULL )
		{
			instance = new Application();
		}
		return instance;
	}

	Application::Application() :
		isRunning( false ),
		timer( NULL ),
		physicsFps( DEFAULT_PHYSICS_FPS ),
		curScene( NULL )
	{
	}

	Application::~Application()
	{
		if ( window.IsOpened() )
		{
			window.Close();
		}
	}

	void Application::SetPhysicsFPS( float fps )
	{
		physicsFps = fps;
	}

	bool Application::Initialize( int width, int height, int bpp, std::string title )
	{
		this->timer = new gdn::Timer();
		this->width = width;
		this->height = height;
		this->bpp = bpp;
		this->title = title;

		srand( (unsigned)time( 0 ) );

		window.Create( width, height, bpp, title );
		return window.IsOpened();
	}

	void Application::AddScene( Scene* scene )
	{
		scenes[ scene->GetName() ] = scene;
	}

	void Application::Run()
	{
		// Small safety incase we call run before calling Init()
		if ( !window.IsOpened() )
			return;

		timer->Reset();
		float nextStepFrame = 0.0f;
		isRunning = true;

		SetScene( "splash" );

		while ( isRunning )
		{
			float time = timer->GetElapsedTime();

			while ( time >= nextStepFrame )
			{
				ProcessSystemEvents();
				ProcessGameEvents();

				Step();
				nextStepFrame += 1.0f / physicsFps;
			}

			Draw();
		}
	}

	void Application::ProcessSystemEvents()
	{
		SDL_Event event;
		while ( SDL_PollEvent( &event ) )
		{
			switch ( event.type )
			{
				// TODO: Temp hacks for SDL
				#ifdef WIZ
				case SDL_JOYBUTTONDOWN:
					// TODO: Implement volume control
					break;
				#endif
				case SDL_MOUSEBUTTONDOWN:
					window.mouseDown = true;
					break;

				case SDL_MOUSEBUTTONUP:
					window.mouseDown = false;
					break;

				case SDL_MOUSEMOTION:
					window.mouseX = event.motion.x;
					window.mouseY = event.motion.y;
					break;

				case SDL_QUIT:
					isRunning = false;
					break;

				case SDL_KEYDOWN:
					#ifdef WIZ
					isRunning = false;
					#else
					if ( event.key.keysym.sym == SDLK_ESCAPE )
					{
						isRunning = false;
					}
					#endif
					break;

				default:
					break;
			}
		}
	}

	void Application::ProcessGameEvents()
	{
		while ( EventMgr.HasEvent( ENGINE ) )
		{
			GameEvent& event = EventMgr.PeekEvent( ENGINE );
			switch ( event.type )
			{
				case GameEvent::ChangeScene:
					//window.SetView( window.GetDefaultView() );
					SetScene( *event.ChangeScene_name );
					break;

				case GameEvent::Quit:
					//window.SetView( window.GetDefaultView() );
					isRunning = false;
					break;

				default:
					break;
			}
			EventMgr.PopEvent( ENGINE );
		}
	}

	void Application::SetScene( std::string name )
	{
		if ( scenes.find( name ) != scenes.end() )
		{
			if ( curScene )
				curScene->Terminate();
			curScene = scenes[ name ];
			curScene->Initialize();
		}
	}

	void Application::Step()
	{
		if ( curScene )
			curScene->Step();
	}

	void Application::Draw()
	{
		// Call draw on the current scene
		if ( curScene )
			curScene->Draw();

		// Calculate fps
		static float lastFrame = timer->GetElapsedTime();
		float curFrame = timer->GetElapsedTime();
		static float avgFPS = 0.0f;
		avgFPS = avgFPS * 0.95f + (1.0f / (curFrame - lastFrame)) * 0.05f;
		lastFrame = curFrame;

		// Display fps
		// TODO: Reimplement FPS counter
		//static sf::String sprite( "", sf::Font::GetDefaultFont(), 12 );
		//sprite.SetPosition( 3, 3 );
		//std::stringstream fps;
		//fps << "FPS: " << (int)avgFPS;
		//sprite.SetText( fps.str() );
		//window.Draw( sprite );

		// Flip buffer
		window.Display();
	}

	int Application::GetWidth()
	{
		return width;
	}

	int Application::GetHeight()
	{
		return height;
	}

	int Application::GetBPP()
	{
		return bpp;
	}

	float Application::GetFPS()
	{
		return physicsFps;
	}

	RenderWindow& Application::GetWindow()
	{
		return window;
	}
}
