#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SFML/Audio.hpp>
#include "WCEngine/Application.h"
#include "Text.h"
#include <string>



class Keyboard
{
public:
	Keyboard();
	virtual ~Keyboard();

	void SetText( std::string newtext );
	std::string GetText();
	bool IsDone();
	bool IsShown();

	void Show();
	void Hide();

	void Step();
	void Draw();

protected:
	std::string text;
	Text textRender;
	bool isMouseDown;
	bool isDone;
	bool isShown;
	float yPos;
	sf::Sound sndClick;

private:
};

#endif // KEYBOARD_H
