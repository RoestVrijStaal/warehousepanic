#include "SceneCredits.h"
#include "WCEngine/Application.h"
#include "WCEngine/EventManager.h"
#include "WCEngine/ResourceManager.h"



SceneCredits::SceneCredits() : Scene( "credits" )
{
    curY = 320;
}

SceneCredits::~SceneCredits()
{
}

void SceneCredits::Initialize()
{
	isMouseDown = true;
}

void SceneCredits::Terminate()
{
}

void SceneCredits::Step()
{
	bool curMouseDown = App.GetWindow().GetInput().IsMouseButtonDown( sf::Mouse::Left );
	if ( curMouseDown and !isMouseDown ) // Mouse down event
	{
		EventMgr.PushEvent( ENGINE, GameEvent::QuitEvent() );
	}
	isMouseDown = curMouseDown;
	curY -= 0.5;
}

void SceneCredits::Draw()
{
	App.GetWindow().Clear( sf::Color( 0, 0, 0 ) );
	float theY = curY;

    std::vector<sf::String> credits_text;

	credits_text.push_back(makeString("Credits"  , 3, theY));
    credits_text.push_back(makeString("Section 1", 2, theY));
    float tmp = theY;
    credits_text.push_back(makeString("Person 1" , 1, theY));
    float tmp2 = theY;
    credits_text.push_back(makeString("Person 2" , 1, theY));
    credits_text.push_back(makeString("Person 3" , 1, theY));
    credits_text.push_back(makeString("Person 4" , 0, tmp));
    credits_text.push_back(makeString("Person 5" , 0, tmp2));
    tmp = theY;




    theY += 10;
    credits_text.push_back(makeString("Section 2", 2, theY));
    tmp = theY;
    credits_text.push_back(makeString("Person 6" , 1, theY));
    credits_text.push_back(makeString("Person 7" , 1, theY));
    credits_text.push_back(makeString("Person 8" , 0, tmp));
    theY += 100;
    credits_text.push_back(makeString("Goodbye!" , 3, theY));

	for (unsigned int i = 0; i < credits_text.size(); i++)
	{
	    App.GetWindow().Draw(credits_text[i]);
	}
}

sf::String SceneCredits::makeString(std::string text, int hlevel, float &yToSet)
{
    if (hlevel == 3)
    {
        sf::String thestring( text, sf::Font::GetDefaultFont(),30 );
        thestring.SetPosition( (320 - thestring.GetRect().GetWidth()) / 2, yToSet );
        yToSet += thestring.GetRect().GetHeight() + 10;
        return thestring;
    }
    else if (hlevel == 2)
    {
        sf::String thestring( text, sf::Font::GetDefaultFont(),17 );
        thestring.SetPosition( (320 - thestring.GetRect().GetWidth()) / 4, yToSet );
        yToSet += thestring.GetRect().GetHeight() + 5;
        return thestring;
    }
    else if (hlevel == 1)
    {
        sf::String thestring( text, sf::Font::GetDefaultFont(),12 );
        thestring.SetPosition( (320 - thestring.GetRect().GetWidth()) / 3, yToSet );
        yToSet += thestring.GetRect().GetHeight() + 2;
        return thestring;
    }
    else if (hlevel == 0)
    {
        sf::String thestring( text, sf::Font::GetDefaultFont(),12 );
        thestring.SetPosition( (320 - thestring.GetRect().GetWidth()) / 3 * 2, yToSet );
        yToSet += thestring.GetRect().GetHeight() + 2;
        return thestring;
    }
    return sf::String();
}

// This makes sure the scene is added to the engine!
SceneCredits* credits = new SceneCredits();
