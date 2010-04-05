#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Text.h"
#include <string>

class Keyboard
{
public:
	Keyboard( int maxLength = 20 );
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
	int timer; // Countdown to know when to delete the excess character (when typed too many)
	std::string text;
	int maxStringLength;
	int lastKeyPress;
	Text textRender;
	bool isMouseDown;
	bool isDone;
	bool isShown;
	float yPos;
	gdn::Sound sndClick;

private:
};

#endif // KEYBOARD_H
