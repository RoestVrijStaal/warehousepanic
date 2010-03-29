#include "Keyboard.h"

#include "WCEngine/GDN.h"

Keyboard::Keyboard()
{
	isDone = false;
	isShown = false;
	yPos = App.GetHeight();
	sndClick = gdn::Sound( ResMgr.GetSound( "click" ) );
}

Keyboard::~Keyboard()
{
}

void Keyboard::SetText( std::string newtext )
{
	text = newtext;
}

std::string Keyboard::GetText()
{
	return text;
}

bool Keyboard::IsShown()
{
	return isShown;
}

bool Keyboard::IsDone()
{
	return isDone;
}

void Keyboard::Show()
{
	isShown = true;
}

void Keyboard::Hide()
{
	isShown = false;
}

void Keyboard::Step()
{
	bool curMouseDown = App.GetWindow().IsMouseButtonDown();

	// Animate keyboard
	if ( isShown )
		yPos += ( 0 - yPos ) / 7.0f;
	else
		yPos += ( App.GetHeight() - yPos ) / 10.0f;

	// Don't add key presses if keyboard is not shown
	if ( !isShown and yPos > 10.0f )
		return;

	if (curMouseDown and !isMouseDown)
	{
		gdn::Vector2f mouse(App.GetWindow().GetMouseX(), App.GetWindow().GetMouseY());
		if (mouse.x > 12 and mouse.x < 38 and mouse.y > 120 and mouse.y < 146)
		{
			SetText(GetText().append("Q"));
			sndClick.Play();
		}
		else if (mouse.x > 42 and mouse.x < 68 and mouse.y > 120 and mouse.y < 146)
		{
			SetText(GetText().append("W"));
			sndClick.Play();
		}
		else if (mouse.x > 72 and mouse.x < 98 and mouse.y > 120 and mouse.y < 146)
		{
			SetText(GetText().append("E"));
			sndClick.Play();
		}
		else if (mouse.x > 102 and mouse.x < 128 and mouse.y > 120 and mouse.y < 146)
		{
			SetText(GetText().append("R"));
			sndClick.Play();
		}
		else if (mouse.x > 132 and mouse.x < 158 and mouse.y > 120 and mouse.y < 146)
		{
			SetText(GetText().append("T"));
			sndClick.Play();
		}
		else if (mouse.x > 162 and mouse.x < 188 and mouse.y > 120 and mouse.y < 146)
		{
			SetText(GetText().append("Y"));
			sndClick.Play();
		}
		else if (mouse.x > 192 and mouse.x < 218 and mouse.y > 120 and mouse.y < 146)
		{
			SetText(GetText().append("U"));
			sndClick.Play();
		}
		else if (mouse.x > 222 and mouse.x < 248 and mouse.y > 120 and mouse.y < 146)
		{
			SetText(GetText().append("I"));
			sndClick.Play();
		}
		else if (mouse.x > 252 and mouse.x < 278 and mouse.y > 120 and mouse.y < 146)
		{
			SetText(GetText().append("O"));
			sndClick.Play();
		}
		else if (mouse.x > 282 and mouse.x < 308 and mouse.y > 120 and mouse.y < 146)
		{
			SetText(GetText().append("P"));
			sndClick.Play();
		}
		else if (mouse.x > 27 and mouse.x < 53 and mouse.y > 150 and mouse.y < 176)
		{
			SetText(GetText().append("A"));
			sndClick.Play();
		}
		else if (mouse.x > 57 and mouse.x < 83 and mouse.y > 150 and mouse.y < 176)
		{
			SetText(GetText().append("S"));
			sndClick.Play();
		}
		else if (mouse.x > 87 and mouse.x < 113 and mouse.y > 150 and mouse.y < 176)
		{
			SetText(GetText().append("D"));
			sndClick.Play();
		}
		else if (mouse.x > 117 and mouse.x < 143 and mouse.y > 150 and mouse.y < 176)
		{
			SetText(GetText().append("F"));
			sndClick.Play();
		}
		else if (mouse.x > 147 and mouse.x < 173 and mouse.y > 150 and mouse.y < 176)
		{
			SetText(GetText().append("G"));
			sndClick.Play();
		}
		else if (mouse.x > 177 and mouse.x < 203 and mouse.y > 150 and mouse.y < 176)
		{
			SetText(GetText().append("H"));
			sndClick.Play();
		}
		else if (mouse.x > 207 and mouse.x < 233 and mouse.y > 150 and mouse.y < 176)
		{
			SetText(GetText().append("J"));
			sndClick.Play();
		}
		else if (mouse.x > 237 and mouse.x < 263 and mouse.y > 150 and mouse.y < 176)
		{
			SetText(GetText().append("K"));
			sndClick.Play();
		}
		else if (mouse.x > 267 and mouse.x < 293 and mouse.y > 150 and mouse.y < 176)
		{
			SetText(GetText().append("L"));
			sndClick.Play();
		}
		else if (mouse.x > 42 and mouse.x < 68 and mouse.y > 180 and mouse.y < 206)
		{
			SetText(GetText().append("Z"));
			sndClick.Play();
		}
		else if (mouse.x > 72 and mouse.x < 98 and mouse.y > 180 and mouse.y < 206)
		{
			SetText(GetText().append("X"));
			sndClick.Play();
		}
		else if (mouse.x > 102 and mouse.x < 128 and mouse.y > 180 and mouse.y < 206)
		{
			SetText(GetText().append("C"));
			sndClick.Play();
		}
		else if (mouse.x > 132 and mouse.x < 158 and mouse.y > 180 and mouse.y < 206)
		{
			SetText(GetText().append("V"));
			sndClick.Play();
		}
		else if (mouse.x > 162 and mouse.x < 188 and mouse.y > 180 and mouse.y < 206)
		{
			SetText(GetText().append("B"));
			sndClick.Play();
		}
		else if (mouse.x > 192 and mouse.x < 218 and mouse.y > 180 and mouse.y < 206)
		{
			SetText(GetText().append("N"));
			sndClick.Play();
		}
		else if (mouse.x > 222 and mouse.x < 248 and mouse.y > 180 and mouse.y < 206)
		{
			SetText(GetText().append("M"));
			sndClick.Play();
		}
		else if (mouse.x > 252 and mouse.x < 300 and mouse.y > 180 and mouse.y < 206
				 and GetText().length() > 0)
		{
			std::string tmp = GetText();
			tmp.erase(tmp.end() - 1);
			SetText(tmp);
			sndClick.Play();
		}
		else if (mouse.x > 57 and mouse.x < 233 and mouse.y > 210 and mouse.y < 236)
		{
			SetText(GetText().append(" "));
			sndClick.Play();
		}
		else if (mouse.x > 237 and mouse.x < 308 and mouse.y > 210 and mouse.y < 236)
		{
			isDone = true;
			sndClick.Play();
		}
	}
	isMouseDown = curMouseDown;
}

void Keyboard::Draw()
{
	// Only draw if visible
	if ( yPos < App.GetHeight() )
	{
		gdn::Sprite theKeyboard( ResMgr.GetImage( "keyboard" ) );
		theKeyboard.SetPosition( 0, yPos );
		textRender.SetText( text );
		textRender.SetPosition( 20, 90 + yPos );
		textRender.SetSize( Text::MEDIUM );
		App.GetWindow().Draw( theKeyboard );
		textRender.Draw();
	}
}
