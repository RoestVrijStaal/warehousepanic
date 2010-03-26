#include "RenderWindow.h"

#include "Image.h"
#include "Sprite.h"


namespace gdn
{
	RenderWindow::RenderWindow() : screen( NULL ), joystick( NULL )
	{
	}

	RenderWindow::~RenderWindow()
	{
		if ( screen )
		{
			SDL_Quit();
		}
	}

	bool RenderWindow::Create( int width, int height, int bpp, std::string title )
	{
		bool isFailed = SDL_Init( SDL_INIT_EVERYTHING );
		if ( isFailed )
		{
			return false;
		}
		screen = SDL_SetVideoMode( width, height, bpp, SDL_SWSURFACE );
		joystick = SDL_JoystickOpen( 0 );
		SDL_JoystickEventState( SDL_DISABLE );

		return screen != NULL;
	}

	void RenderWindow::Close()
	{
		if ( screen )
		{
			SDL_JoystickClose( joystick );
			SDL_Quit();
			screen = NULL;
			joystick = NULL;
		}
	}

	bool RenderWindow::IsOpened()
	{
		return screen != NULL;
	}

	void RenderWindow::Draw( gdn::Sprite& sprite )
	{
		Image* img = sprite.GetImage();
		if ( !img )
			return;

		SDL_Rect rect;
		rect.x = sprite.GetPosition().x - sprite.GetCenter().x;
		rect.y = sprite.GetPosition().y - sprite.GetCenter().y;
		rect.w = img->GetWidth();
		rect.h = img->GetHeight();
		SDL_BlitSurface( img->GetTexture(), NULL, screen, &rect );
	}

	void RenderWindow::Clear( unsigned char r, unsigned char g, unsigned char b )
	{
		SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, r, g, b ) );
	}

	void RenderWindow::Display()
	{
		if ( screen )
		{
			SDL_Flip( screen );
		}
	}

	bool RenderWindow::IsMouseButtonDown()
	{
		return mouseDown;
	}

	float RenderWindow::GetMouseX()
	{
		return mouseX;
	}

	float RenderWindow::GetMouseY()
	{
		return mouseY;
	}
}
