#include "Application.h"

#include "EventManager.h"
#include "Scene.h"
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <iostream>


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
	this->width = width;
	this->height = height;
	this->bpp = bpp;
	this->title = title;

	srand( (unsigned)time( 0 ) );

	window.Create( sf::VideoMode( width, height, bpp ), title, sf::Style::Close );
	return window.IsOpened();
}

void Application::AddScene( Scene* scene )
{
	scenes[ scene->GetName() ] = scene;
	scene->SetRenderWindow( window );
}

void Application::Run()
{
	// Small safety incase we call run before calling Init()
	if ( !window.IsOpened() )
		return;

	timer.Reset();
	float nextStepFrame = 0.0f;
	isRunning = true;

	SetScene( "menu" );

	while ( isRunning )
	{
		float time = timer.GetElapsedTime();

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
	sf::Event event;
	while ( window.GetEvent( event ) )
	{
		switch ( event.Type )
		{
			case sf::Event::Closed:
				isRunning = false;
				break;

			case sf::Event::KeyPressed:
				switch ( event.Key.Code )
				{
					case sf::Key::Escape:
						isRunning = false;
						break;

					default:
						break;
				}
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
				window.SetView( window.GetDefaultView() );
				SetScene( *event.ChangeScene_name );
				break;

			case GameEvent::Quit:
				window.SetView( window.GetDefaultView() );
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
	static float lastFrame = timer.GetElapsedTime();
	float curFrame = timer.GetElapsedTime();
	static float avgFPS = 0.0f;
	avgFPS = avgFPS * 0.95f + (1.0f / (curFrame - lastFrame)) * 0.05f;
	lastFrame = curFrame;

	// Display fps
	static sf::String sprite( "", sf::Font::GetDefaultFont(), 12 );
	sprite.SetPosition( 3, 3 );
	std::stringstream fps;
	fps << "FPS: " << (int)avgFPS;
	sprite.SetText( fps.str() );
	window.Draw( sprite );

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

sf::RenderWindow& Application::GetWindow()
{
	return window;
}
