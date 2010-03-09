//Couldn't get it to work without this line :/
#include "WCEngine/ResourceManager.h"

#include "Keyboard.h"

Keyboard::Keyboard()
{
	//ctor
	done = false;
}

Keyboard::~Keyboard()
{
	//dtor
}

void Keyboard::SetText( std::string newtext )
{
    text = newtext;
}

std::string Keyboard::GetText()
{
    return text;
}

bool Keyboard::GetDone()
{
    if (done == true)
    {
        //Dunno why, but I have to put it opposite to work right.
        return false;
    }
    return true;
}

void Keyboard::Step()
{
    if (App.GetWindow().GetInput().IsMouseButtonDown(sf::Mouse::Left) and isMouseDown == false)
    {
        sf::Vector2f mouse(App.GetWindow().GetInput().GetMouseX(),App.GetWindow().GetInput().GetMouseY());
        if (mouse.x > 12 and mouse.x < 38 and mouse.y > 120 and mouse.y < 146)
        {
            SetText(GetText().append("Q"));
        }
        else if (mouse.x > 42 and mouse.x < 68 and mouse.y > 120 and mouse.y < 146)
        {
            SetText(GetText().append("W"));
        }
        else if (mouse.x > 72 and mouse.x < 98 and mouse.y > 120 and mouse.y < 146)
        {
            SetText(GetText().append("E"));
        }
        else if (mouse.x > 102 and mouse.x < 128 and mouse.y > 120 and mouse.y < 146)
        {
            SetText(GetText().append("R"));
        }
        else if (mouse.x > 132 and mouse.x < 158 and mouse.y > 120 and mouse.y < 146)
        {
            SetText(GetText().append("T"));
        }
        else if (mouse.x > 162 and mouse.x < 188 and mouse.y > 120 and mouse.y < 146)
        {
            SetText(GetText().append("Y"));
        }
        else if (mouse.x > 192 and mouse.x < 218 and mouse.y > 120 and mouse.y < 146)
        {
            SetText(GetText().append("U"));
        }
        else if (mouse.x > 222 and mouse.x < 248 and mouse.y > 120 and mouse.y < 146)
        {
            SetText(GetText().append("I"));
        }
        else if (mouse.x > 252 and mouse.x < 278 and mouse.y > 120 and mouse.y < 146)
        {
            SetText(GetText().append("O"));
        }
        else if (mouse.x > 282 and mouse.x < 308 and mouse.y > 120 and mouse.y < 146)
        {
            SetText(GetText().append("P"));
        }
        else if (mouse.x > 27 and mouse.x < 53 and mouse.y > 150 and mouse.y < 176)
        {
            SetText(GetText().append("A"));
        }
        else if (mouse.x > 57 and mouse.x < 83 and mouse.y > 150 and mouse.y < 176)
        {
            SetText(GetText().append("S"));
        }
        else if (mouse.x > 87 and mouse.x < 113 and mouse.y > 150 and mouse.y < 176)
        {
            SetText(GetText().append("D"));
        }
        else if (mouse.x > 117 and mouse.x < 143 and mouse.y > 150 and mouse.y < 176)
        {
            SetText(GetText().append("F"));
        }
        else if (mouse.x > 147 and mouse.x < 173 and mouse.y > 150 and mouse.y < 176)
        {
            SetText(GetText().append("G"));
        }
        else if (mouse.x > 177 and mouse.x < 203 and mouse.y > 150 and mouse.y < 176)
        {
            SetText(GetText().append("H"));
        }
        else if (mouse.x > 207 and mouse.x < 233 and mouse.y > 150 and mouse.y < 176)
        {
            SetText(GetText().append("J"));
        }
        else if (mouse.x > 237 and mouse.x < 263 and mouse.y > 150 and mouse.y < 176)
        {
            SetText(GetText().append("K"));
        }
        else if (mouse.x > 267 and mouse.x < 293 and mouse.y > 150 and mouse.y < 176)
        {
            SetText(GetText().append("L"));
        }
        else if (mouse.x > 42 and mouse.x < 68 and mouse.y > 180 and mouse.y < 206)
        {
            SetText(GetText().append("Z"));
        }
        else if (mouse.x > 72 and mouse.x < 98 and mouse.y > 180 and mouse.y < 206)
        {
            SetText(GetText().append("X"));
        }
        else if (mouse.x > 102 and mouse.x < 128 and mouse.y > 180 and mouse.y < 206)
        {
            SetText(GetText().append("C"));
        }
        else if (mouse.x > 132 and mouse.x < 158 and mouse.y > 180 and mouse.y < 206)
        {
            SetText(GetText().append("V"));
        }
        else if (mouse.x > 162 and mouse.x < 188 and mouse.y > 180 and mouse.y < 206)
        {
            SetText(GetText().append("B"));
        }
        else if (mouse.x > 192 and mouse.x < 218 and mouse.y > 180 and mouse.y < 206)
        {
            SetText(GetText().append("N"));
        }
        else if (mouse.x > 222 and mouse.x < 248 and mouse.y > 180 and mouse.y < 206)
        {
            SetText(GetText().append("M"));
        }
        else if (mouse.x > 252 and mouse.x < 300 and mouse.y > 180 and mouse.y < 206
                 and GetText().length() > 0)
        {
            std::string tmp = GetText();
            tmp.erase(tmp.end() - 1);
            SetText(tmp);
        }
        else if (mouse.x > 57 and mouse.x < 233 and mouse.y > 210 and mouse.y < 236)
        {
            SetText(GetText().append(" "));
        }
        else if (mouse.x > 237 and mouse.x < 308 and mouse.y > 210 and mouse.y < 236)
        {
            done = true;
        }
    }
    isMouseDown = App.GetWindow().GetInput().IsMouseButtonDown(sf::Mouse::Left);
}

void Keyboard::Draw( sf::RenderWindow& window)
{
    sf::Sprite theKeyboard(ResMgr.GetImage( "keyboard" ));
    sf::String theText(text);
    theText.SetPosition(15,80);
    App.GetWindow().Draw(theKeyboard);
    App.GetWindow().Draw(theText);
}
