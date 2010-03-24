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

    std::vector<Text> credits_text;

	credits_text.push_back( Text() );   // Wouldn't draw CREDITS otherwise.
	credits_text.push_back(makeString("CREDITS"  , 3, theY));
    credits_text.push_back(makeString("SECTION 1", 2, theY));
    float tmp = theY;
    credits_text.push_back(makeString("PERSON 1" , 1, theY));
    float tmp2 = theY;
    credits_text.push_back(makeString("PERSON 2" , 1, theY));
    credits_text.push_back(makeString("PERSON 3" , 1, theY));
    credits_text.push_back(makeString("PERSON 4" , 0, tmp ));
    credits_text.push_back(makeString("PERSON 5" , 0, tmp2));
    tmp = theY;




    theY += 10;
    credits_text.push_back(makeString("SECTION 2", 2, theY));
    tmp = theY;
    credits_text.push_back(makeString("PERSON 6" , 1, theY));
    credits_text.push_back(makeString("PERSON 7" , 1, theY));
    credits_text.push_back(makeString("PERSON 8" , 0, tmp ));
    theY += 100;
    credits_text.push_back(makeString("GOODBYE"  , 3, theY));

	for (int i = 1; i < credits_text.size(); i++)
	{
	    credits_text[i].Draw();
	}
}

Text SceneCredits::makeString(std::string text, float hlevel, float &yToSet)
{
    if (hlevel == 3)
    {
        Text thestring( text, (320 - thestring.GetRect().GetWidth()) / 3.5, yToSet, Text::LARGE );
        yToSet += thestring.GetRect().GetHeight() + 8;
        return thestring;
    }
    else if (hlevel == 2)
    {
        Text thestring( text, (320 - thestring.GetRect().GetWidth()) / 4.5, yToSet, Text::MEDIUM );
        yToSet += thestring.GetRect().GetHeight() + 5;
        return thestring;
    }
    else if (hlevel == 1)
    {
        Text thestring( text, (320 - thestring.GetRect().GetWidth()) / 3.5, yToSet, Text::SMALL );
        yToSet += thestring.GetRect().GetHeight() + 2;
        return thestring;
    }
    else if (hlevel == 0)
    {
        Text thestring( text, (int)(320 - thestring.GetRect().GetWidth()) / 3.5 * 2, (int)yToSet, Text::SMALL );
        yToSet += thestring.GetRect().GetHeight() + 2;
        return thestring;
    }
    return Text();
}

// This makes sure the scene is added to the engine!
SceneCredits* credits = new SceneCredits();
