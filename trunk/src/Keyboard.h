#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "WCEngine/Application.h"
#include <string>


class Keyboard
{
	public:
		Keyboard();
		virtual ~Keyboard();

		void SetText( std::string newtext );
		std::string GetText();

		void Step();
		void Draw( sf::RenderWindow& window );

	protected:
		std::string text;
		bool isMouseDown;

	private:
};

#endif // KEYBOARD_H
