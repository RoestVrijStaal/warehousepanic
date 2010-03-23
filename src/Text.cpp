#include "Text.h"

#include "WCEngine/Application.h"
#include "WCEngine/ResourceManager.h"
#include "Functions.h"



Text::Text( std::string newtext, int x, int y, Size newsize ) :
	text( newtext ),
	pos( x, y ),
	size( newsize )
{
}

Text::~Text()
{
}

void Text::SetText( std::string newtext )
{
	text = newtext;
}

void Text::SetPosition( sf::Vector2f& newpos )
{
	pos = newpos;
}

void Text::SetPosition( float x, float y )
{
	pos.x = x;
	pos.y = y;
}

void Text::SetSize( Size newsize )
{
    if ( newsize == SMALL or newsize == MEDIUM or newsize == LARGE )
    {
        size = newsize;
    }
}

void Text::Draw()
{
	sf::RenderWindow& window = App.GetWindow();

	sf::Sprite sprite;
	int charOffset = 0;

	// Prepare string
	std::string character = "A ";
	switch ( size )
	{
		case SMALL: character.append( "small" ); break;
		case MEDIUM: character.append( "medium" ); break;
		case LARGE: character.append( "large" ); break;
		default: break;
	}

	for ( std::string::iterator it = text.begin(); it != text.end(); ++it )
	{
		// Replace first character and get image
		character[0] = *it;
		sf::Image& img = ResMgr.GetImage( character );

		sprite = sf::Sprite( img );
		sprite.SetPosition( pos.x + charOffset, pos.y );
		window.Draw( sprite );

		switch ( size )
		{
			case SMALL: charOffset += img.GetWidth() - 1; break;
			case MEDIUM: charOffset += img.GetWidth() - 2; break;
			case LARGE: charOffset += img.GetWidth() - 3; break;
			default: break;

		}
	}
}
