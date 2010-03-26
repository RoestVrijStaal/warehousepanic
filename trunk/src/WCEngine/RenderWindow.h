#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <string>
#include <SDL/SDL.h>



namespace gdn
{
	class Sprite;

	class RenderWindow
	{
		public:
			RenderWindow();
			virtual ~RenderWindow();

			bool Create( int width, int height, int bpp, std::string title );
			void Close();
			bool IsOpened();
			void Draw( gdn::Sprite& sprite );
			void Clear( unsigned char r, unsigned char g, unsigned char b );
			void Display();

			bool IsMouseButtonDown();
			float GetMouseX();
			float GetMouseY();

			// TODO: Temp hack for SDL until i can cook up something better
			float mouseX;
			float mouseY;
			bool mouseDown;

		protected:
		private:
			SDL_Surface* screen;
			SDL_Joystick* joystick;
	};
}

#endif // RENDERWINDOW_H
